/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:12:29 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/21 12:14:41 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"





void	execute_external(t_cmd *cmd, char **envp)
{
	// Ejecuta el comando externo utilizando execve
	execve(cmd->cmd_path, cmd->cmd_args, envp);

	// Si execve falla, muestra un mensaje de error y termina el proceso
	perror("Error ejecutando comando externo con execve");
	exit(EXIT_FAILURE);
}



int execute_commands(t_mini *mini)
{
	t_list *t_list_exec_cmd = mini->exec->first_cmd;
	t_cmd  *curr_cmd;
	pid_t  pid;
	int    input_fd = STDIN_FILENO;
	int 	pipe_fd[2]; //descriptores de la pipe
	int    i = 0;
	int len_t_list_exec_cmd = ft_lstsize(t_list_exec_cmd);

	while (t_list_exec_cmd)
	{
		curr_cmd = (t_cmd *)t_list_exec_cmd->content;
		curr_cmd->cmd_id = i;
		printf("id: [%d], command: [%s]\n", i, curr_cmd->cmd);
		i++;

		// Crear pipe solo si no es el último comando
		if (t_list_exec_cmd->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("Error creando pipe");
				exit(EXIT_FAILURE);
			}
			curr_cmd->output_fd = pipe_fd[1];
			//salida al extremo de escritura
		}
		else
		{
			curr_cmd->output_fd = STDOUT_FILENO; //utlimo cmd escribe en terminal stdout
		}

		//entrada del comando
		curr_cmd->input_fd = input_fd;
		printf("PID PADRE: [%d]\n", getpid());
		pid = fork();

		if (pid < 0)
		{
			perror("Error creando proceso hijo");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			// Proceso hijo
			printf("Proceso hijo ejecutándose\n");
			printf("PID HIJO: %d\n", getpid());

			//redirigir entrada si no el primer comando
			if (curr_cmd->input_fd != STDIN_FILENO)
			{
				if (dup2(curr_cmd->input_fd, STDIN_FILENO) == -1)
				{
					perror("Error redirigiendo entrada");
					exit(EXIT_FAILURE);
				}
				close(curr_cmd->input_fd);
				//cerrar el descriptor original
			}

			//redirigir la salida si no es el ultimo comando
			if (curr_cmd->output_fd != STDOUT_FILENO)
			{
				if (dup2(curr_cmd->output_fd, STDOUT_FILENO) == -1)
				{
					perror("Errpor redirigiendo salida");
					exit (EXIT_FAILURE);
				}
				//close(curr_cmd->output_fd);
				close(pipe_fd[1]);//cerrar el descriptor original
			}
			char **envp = lst_to_arr(mini->env);

			execute_external(curr_cmd, envp);
			perror("Error ejecutando el comando con execve");
			printf("cmd1: %s\n", curr_cmd->cmd);
			printf("cmd2: %s\n", curr_cmd->cmd_args[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			//proceso padre

			//cerrar el extremo de escritura en la parte del parte si no es el utlimo comando
			if (curr_cmd->output_fd != STDOUT_FILENO)
			{
				close(pipe_fd[1]);
			}
			//cerrar el extremo de lectura anterior e el padre si no es stdin
			if (curr_cmd->input_fd != STDIN_FILENO)
			{
				close(curr_cmd->input_fd);
			}
			if (t_list_exec_cmd->next)
			{
				input_fd = pipe_fd[0];
			}
		}
		t_list_exec_cmd = t_list_exec_cmd->next;
	}

	//cerrar cualquier descritor de pope restante en el padre
	if (input_fd != STDIN_FILENO)
	{
		close(input_fd);
	}
	//esperar a que todos los hijos terminenes
	int num_children = len_t_list_exec_cmd;
	while (num_children > 0)
	{
		if (wait(NULL) == -1)
		{
			perror("Error esperando proceso hijo");
		}
		else
		{
			num_children--; // Decrementamos el contador de hijos pendientes
		}
	}

	return (TRUE);
}

















/*void	setup_pipes(t_pipe *pipe_info, int cmd_id)
{

	if (cmd_id % 2 && pipe_info->pipe_fds[0] != -1)
	{
		if (dup2(pipe_info->pipe_fds[0], STDIN_FILENO) == -1)
		{
			perror("Error redirigiendo entrada desde el pipe anterior");
			exit(EXIT_FAILURE);
		}
		close(pipe_info->pipe_fds[0]);
		close(pipe_info->pipe_fds[1]);
	}
	else
	{
		if (dup2(pipe_info->pipe_fds[1], STDOUT_FILENO) == -1)
		{
			perror("Error redirigiendo salida hacia el siguiente comando");
			exit(EXIT_FAILURE);
		}
		close(pipe_info->pipe_fds[1]);
		close(pipe_info->pipe_fds[0]);
	}
}*/

/**
 * execute_external - Ejecuta un comando externo con la posibilidad de redirección de entrada/salida.
 * @cmd: Puntero a la estructura que contiene el comando a ejecutar.
 * @envp: Lista de variables de entorno para el proceso.
 *
 * Esta función se encarga de ejecutar un comando externo utilizando execve.
 * Además, maneja la redirección de la entrada y la salida estandar para el proceso hijo.
 */

/*void	execute_external(t_cmd *cmd, char **envp)
{
	// Ejecuta el comando externo utilizando execve
	execve(cmd->cmd_path, cmd->cmd_args, envp);

	// Si execve falla, muestra un mensaje de error y termina el proceso
	perror("Error ejecutando comando externo con execve");
	exit(EXIT_FAILURE);
}



int execute_commands(t_mini *mini)
{
	t_list *t_list_exec_cmd = mini->exec->first_cmd;
	t_cmd  *curr_cmd;
	pid_t  pid;
	int    input_fd = STDIN_FILENO;
	t_pipe *pipe_info = init_pipe();
	int    i = 0;

	if (!pipe_info)
	{
		perror("Error inicializando pipe_info");
		return (1);
	//	exit(EXIT_FAILURE);
	}
	int len_t_list_exec_cmd = ft_lstsize(t_list_exec_cmd);
	printf("len t_list_exec_cmd: %d\n", len_t_list_exec_cmd);
	while (t_list_exec_cmd)
	{
		curr_cmd = (t_cmd *)t_list_exec_cmd->content;
		curr_cmd->cmd_id = i;
		printf("id: [%d], command: [%s]\n", i, curr_cmd->cmd);
		i++;

		// Crear pipe solo si no es el último comando
		if (t_list_exec_cmd->next)
		{
			if (pipe(pipe_info->pipe_fds) == -1)
			{
				perror("Error creando pipe");
				exit(EXIT_FAILURE);
			}
			// la salida del comanda de la izquierda a la entrada de la pipe
			curr_cmd->output_fd = pipe_info->pipe_fds[1];
		}
		else
		{
			curr_cmd->output_fd = STDOUT_FILENO;
		}

		curr_cmd->input_fd = input_fd;
		printf("PID PADRE: [%d]\n", getpid());
		pid = fork();

		if (pid < 0)
		{
			perror("Error creando proceso hijo");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			// Proceso hijo
			printf("Proceso hijo ejecutándose\n");
			printf("PID HIJO: %d\n", getpid());
			if (len_t_list_exec_cmd >= 2)
			{
				setup_pipes(pipe_info, curr_cmd->cmd_id);
			}

			char **envp = lst_to_arr(mini->env);

			execute_external(curr_cmd, envp);
			//close(pipe_info->pipe_fds[1]);
			perror("Error ejecutando el comando con execve");
			printf("cmd1: %s\n", curr_cmd->cmd);
			printf("cmd2: %s\n", curr_cmd->cmd_args[0]);
			free(pipe_info);
			exit(EXIT_FAILURE);
		}
		t_list_exec_cmd = t_list_exec_cmd->next;
	}
	// Cerramos canal 3 y 4 del padre
	close(pipe_info->pipe_fds[0]);
	close(pipe_info->pipe_fds[1]);
	printf("pipe_info->pipe_fds[0]: %d\n", pipe_info->pipe_fds[0]);
	printf("pipe_info->pipe_fds[1]: %d\n", pipe_info->pipe_fds[1]);
//	waitpid(-1, NULL, 0);
	//wait(NULL);
	//wait(NULL);
	//return (TRUE);
	int num_children = len_t_list_exec_cmd;
	while (num_children > 0)
	{
		if (wait(NULL) == -1)
		{
			perror("Error esperando proceso hijo");
		}
		else
		{
			num_children--; // Decrementamos el contador de hijos pendientes
		}
	}

	free(pipe_info);
	return (TRUE);
}
*/