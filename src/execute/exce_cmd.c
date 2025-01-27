/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/26 00:55:10 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:12:29 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/22 17:31:04 by  dasalaza        ###   ########.fr       */
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
		i ++;
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
		// printf("PID PADRE: [%d]\n", getpid());
		pid = fork();

		if (pid < 0)
		{
			perror("Error creando proceso hijo");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			// Proceso hijo
			// printf("Proceso hijo ejecutándose\n");
			// printf("PID HIJO: %d\n", getpid());

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

			if (curr_cmd->is_external == 1)
			{
				printf("flag: [%d]\n", curr_cmd->is_external);
				printf("entra como externo pero no deberia\n");
				execute_external(curr_cmd, envp);
			}
			else if (curr_cmd->is_builtin == 1)
			{
				cases_builtins(mini);
			}
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