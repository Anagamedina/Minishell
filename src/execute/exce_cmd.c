/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:12:29 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/19 11:48:38 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"


//***************IDEAS*************************/

//1_una funcion que ejecute builtins tomando como argumento char **cmd_list y y un char *tmp_cmd

//2_funcion para  crear una funcion que cree una pipe, y adjudicando el ultimo pipe como el utlimo, y que segun el indice de la pipe haga una cosa u otra es decir si son pipes intermedias o la utlima

//3_una funcion que ejecute comandos externos tomando como argumento t_cmd *cmd , t_pipe *pipes , int id_cmd

//4_crear una funcion que cuente el numero de pipes (|) que hay, asi podremos saber si hay un pipe al inicio p fimal de la entrada y si hay pipes duplicados

//5_una funcion que splitee comandos con pipes creo que era asi,

//6_ otra funcion qeu mire que cada subcomando esta vacio por ejemplo si hay un pipe sin comandos antes o despues, y si hay un pipe vacio entre dos comandos se debe ignorar


void	setup_pipes(t_pipe *pipe_info, int cmd_id, t_mini *mini)
{

	if (cmd_id % 2 == 1 && pipe_info->pipe_fds[0] != -1)
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
		close(pipe_info->pipe_fds[0]);	//add by dasalaza
		close(pipe_info->pipe_fds[1]);	//add by dasalaza
	}
}

/**
 * execute_external - Ejecuta un comando externo con la posibilidad de redirección de entrada/salida.
 * @cmd: Puntero a la estructura que contiene el comando a ejecutar.
 * @envp: Lista de variables de entorno para el proceso.
 *
 * Esta función se encarga de ejecutar un comando externo utilizando execve.
 * Además, maneja la redirección de la entrada y la salida estandar para el proceso hijo.
 */

void execute_external(t_cmd *cmd, char **envp)
{
	// Ejecuta el comando externo utilizando execve
	execve(cmd->cmd_path, cmd->cmd_args, envp);

	// Si execve falla, muestra un mensaje de error y termina el proceso
	perror("Error ejecutando comando externo con execve");
	exit(EXIT_FAILURE);
}


void execute_commands(t_mini *mini)
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
		return;
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
			curr_cmd->output_fd = pipe_info->pipe_fds[0];
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
				setup_pipes(pipe_info, curr_cmd->cmd_id, mini);
			}

			char **envp = lst_to_arr(mini->env);
			execute_external(curr_cmd, envp);
			perror("Error ejecutando el comando con execve");
			exit(EXIT_FAILURE);
		}
		t_list_exec_cmd = t_list_exec_cmd->next;
	}
	// Cerramos canal 3 y 4 del padre
	close(pipe_info->pipe_fds[0]);
	close(pipe_info->pipe_fds[1]);

	waitpid(-1, NULL, 0);
	// free(pipe_info); // Liberar la memoria asignada a pipe_info
}





//******************START***********************/

//funcion para Redigir la entrada y salida de los comandos externos y builtins

/*void setup_pipes(t_pipe *pipe, int cmd_id, t_mini *mini)
{
	int total_cmds = ft_lstsize(mini->exec->first_cmd);

	// Si no es el primer comando, redirigir la entrada estándar
	if (cmd_id > 0)
	{
		if (dup2(pipe->in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 in_fd");
			exit(EXIT_FAILURE);
		}
	}

	// Si no es el último comando, redirigir la salida estándar
	if (cmd_id < total_cmds - 1)
	{
		if (dup2(pipe->out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 out_fd");
			exit(EXIT_FAILURE);
		}
	}
}

void execute_external(t_cmd *cmd, char **envp)
{
	if (cmd->input_fd != -1)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
		{
			perror("Error redirigiendo entrada");
			exit(EXIT_FAILURE);
		}
		close(cmd->input_fd);
	}
	if (cmd->output_fd != -1)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
		{
			perror("Error redirigiendo salida");
			exit(EXIT_FAILURE);
		}
		close(cmd->output_fd);
	}
	if (cmd->is_external)
	{
		execve(cmd->cmd_path, cmd->cmd_args, envp);
		perror("Error ejecutando comando externo");
		exit(EXIT_FAILURE);
	} else
	{
		printf("Comando builtin: %s\n", cmd->cmd);
		exit(EXIT_SUCCESS);
	}
}

void handle_commands(t_mini *mini)
{
	t_list *current;
	t_cmd *cmd;
	pid_t pid;
	int pipe_fd[2];
	int input_fd = -1;
	t_pipe *pipe_info = init_pipe();

	current = mini->exec->first_cmd;
	while (current) {
		cmd = (t_cmd *)current->content;

		if (current->next) {
			if (pipe(pipe_fd) == -1) {
				perror("Error creando pipe");
				exit(EXIT_FAILURE);
			}
			pipe_info->out_fd = pipe_fd[1];
			cmd->output_fd = pipe_fd[1];
		}
		else
			pipe_info->out_fd = -1;  // Si es el último comando, ya no tiene salida

		cmd->input_fd = input_fd;
		pid = fork();

		if (pid < 0) {
			perror("Error creando proceso hijo");
			exit(EXIT_FAILURE);
		}

		if (pid == 0) {
			setup_pipes(pipe_info, cmd->cmd_id, mini);  // Configura las redirecciones para este proceso
			execute_external(cmd, lst_to_arr(mini->env));
		}
		else
		{
			if (cmd->input_fd != -1)
			{
				close(cmd->input_fd);  // Cierra el descriptor de entrada del proceso anterior
			}
			if (pipe_info->out_fd != -1) {
				close(pipe_info->out_fd);  // Cierra el descriptor de salida del pipe
			}
			input_fd = pipe_fd[0];  // Establece el nuevo input para el siguiente comando
			waitpid(pid, NULL, 0);  // Espera al proceso hijo
		}

		current = current->next;  // Avanza al siguiente comando
	}
}
 */


 //******************COPIA**************************/

/*void	execute_external(t_cmd *cmd, int input_fd, int pipe_fd[2], char **envp)
{
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("Error redirigiendo entrada");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}

	if (pipe_fd)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("Error redirigiendo salida");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}

	if (cmd->is_external)
	{
		execve(cmd->cmd_path, cmd->cmd_args, envp);
		perror("Error ejecutando comando externo");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Comando builtin: %s\n", cmd->cmd);
		exit(EXIT_SUCCESS);
	}
}

void	handle_commands(t_mini *mini)
{
	t_list	*current;
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_pipe_fd = -1; // Descriptor de lectura del pipe anterior
	pid_t	pid;

	current = mini->exec->first_cmd;
	while (current)
	{
		cmd = (t_cmd *)current->content;

		if (current->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("Error creando pipe");
				exit(EXIT_FAILURE);
			}
		}

		pid = fork();
		if (pid < 0)
		{
			perror("Error creando proceso hijo");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			execute_external(cmd, prev_pipe_fd, pipe_fd, lst_to_arr(mini->env));
		}
		else
		{
			if (prev_pipe_fd != -1)
				close(prev_pipe_fd);
			if (current->next)
				close(pipe_fd[1]);
			prev_pipe_fd = pipe_fd[0];
			waitpid(pid, NULL, 0);
		}

		current = current->next;
	}
}
*/


/*static void	execute_external(t_cmd *cmd, char **envp)
{
	if (cmd->input_fd != -1)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
		{
			perror("Error duplicando input_fd para comando externo");
			exit(EXIT_FAILURE);
		}
		close(cmd->input_fd);
	}

	if (cmd->output_fd != -1)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
		{
			perror("Error duplicando output_fd para comando externo");
			exit(EXIT_FAILURE);
		}
		close(cmd->output_fd);
	}
	execve(cmd->cmd_path, cmd->cmd_args, envp);
	perror("Error ejecutando comando externo");
	exit(EXIT_FAILURE);
}
*/

/*
void	handle_commands(t_mini *mini)
{
	t_list	*current;
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_pipe_fd = -1;
	//int		pre_pipe_end[2] = {-1, -1};

	current = mini->exec->first_cmd;
	while (current)
	{
		cmd = (t_cmd *)current->content;

		if (cmd->is_builtin)
		{
			//execute_builtin(cmd);
			printf("Comando builtin: %s\n", cmd->cmd);
		}
		else if (cmd->is_external)
		{
			pipe(pipe_fd);
			cmd->pipe[0] = pipe_fd[0];
			cmd->pipe[1] = pipe_fd[1];
			pid_t pid = fork();
			if (pid < 0)
			{
				perror("Error creando proceso hijo");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				execute_external(cmd, lst_to_arr(mini->env));
			}
			else
			{
				wait(NULL);
				if (prev_pipe_fd[0] != -1)
					close(prev_pipe_fd[0]);
				close(pipe_fd[1]);
				prev_pipe_fd[0] = pipe_fd[0];
			}
		}

		current = current->next;
	}
}*/