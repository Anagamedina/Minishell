/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/16 19:06:10 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_external(t_cmd *cmd, char **envp)
{
	execve(cmd->cmd_path, cmd->cmd_args, envp);
	perror("Error ejecutando comando externo con execve");
	exit(EXIT_FAILURE);
}

static void setup_fds(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
	// Si no es el último comando, crear un pipe
	if (!curr_cmd->last_cmd)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Error creando pipe");
			exit(EXIT_FAILURE);
		}
		if (curr_cmd->redir_list == NULL) // Si no hay `>` redirigir a `pipe_fd[1]`
			curr_cmd->output_fd = pipe_fd[1];
	}
	else
	{
		curr_cmd->output_fd = STDOUT_FILENO; // Último comando: salida a STDOUT
	}

	// Asignar la entrada del comando al input actual del pipeline
	curr_cmd->input_fd = *input_fd;
}

void	handle_child(t_cmd *curr_cmd, t_mini *mini)
{
	// Si hay redirección `>`, la aplicamos primero
	if (apply_redirections(curr_cmd) > 0)
	{
		if (dup2(curr_cmd->output_fd, STDOUT_FILENO) == -1)
		{
			perror("Error redirigiendo salida a archivo");
			exit(EXIT_FAILURE);
		}
		close(curr_cmd->output_fd);
	}
	else
	{
		// Si no hay redirección, redirigir salida al pipe
		if (curr_cmd->output_fd != STDOUT_FILENO)
		{
			if (dup2(curr_cmd->output_fd, STDOUT_FILENO) == -1)
			{
				perror("Error redirigiendo salida al pipe");
				exit(EXIT_FAILURE);
			}
			close(curr_cmd->output_fd);
		}
	}

	// Redirigir la entrada si no es `STDIN_FILENO`
	if (curr_cmd->input_fd != STDIN_FILENO)
	{
		if (dup2(curr_cmd->input_fd, STDIN_FILENO) == -1)
		{
			perror("Error redirigiendo entrada");
			exit(EXIT_FAILURE);
		}
		close(curr_cmd->input_fd);
	}

	// printf("-----------PRINTING ENV LIST IN HANDLE CHILD---------------\n");
	// print_env_list(mini->env);
	printf("-----------------------------------\n");

	if (curr_cmd->is_external == 1)
	{
		execute_external(curr_cmd, mini->envp_to_array);
		exit(EXIT_FAILURE);
	}
	else if (curr_cmd->is_builtin == 1)
	{
		cases_builtins(mini);
		exit(0);
	}
	exit(EXIT_FAILURE);
}

static void handle_parent(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
	// Cerrar extremos de pipe en el padre para evitar bloqueos
	if (curr_cmd->output_fd != STDOUT_FILENO)
		close(curr_cmd->output_fd);

	if (curr_cmd->input_fd != STDIN_FILENO)
		close(curr_cmd->input_fd);

	// Si hay un siguiente comando, pasamos `pipe_fd[0]` como nueva entrada
	if (!curr_cmd->last_cmd)
	{
		close(pipe_fd[1]); // Cerrar escritura del pipe en el padre
		*input_fd = pipe_fd[0]; // Pasar la lectura del pipe al siguiente comando
	}
	else
	{
		close(pipe_fd[0]); // Si es el último comando, cerrar lectura
	}
}

static void wait_for_children(int num_children)
{
	while (num_children > 0)
	{
		if (wait(NULL) == -1)
		{
			perror("Error esperando proceso hijo");
		}
		else
		{
			num_children--;
		}
	}
}

int execute_commands(t_mini *mini)
{
	t_list	*t_list_exec_cmd;
	t_cmd	*curr_cmd;
	pid_t	pid;
	int		input_fd;
	int		pipe_fd[2];
	int		i;

	i = 0;
	input_fd = STDIN_FILENO;
	t_list_exec_cmd = mini->exec->first_cmd;
	while (t_list_exec_cmd)
	{
		curr_cmd = (t_cmd *)t_list_exec_cmd->content;
		curr_cmd->cmd_id = i++;

		if (curr_cmd->is_builtin == 1 && curr_cmd->last_cmd && input_fd == STDIN_FILENO)
		{
			cases_builtins(mini);
			return (TRUE);
		}

		setup_fds(curr_cmd, pipe_fd, &input_fd);
		pid = fork();
		if (pid < 0)
		{
			perror("Error creando proceso hijo");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			handle_child(curr_cmd, mini);
		}
		else
		{
			handle_parent(curr_cmd, pipe_fd, &input_fd);
		}
		t_list_exec_cmd = t_list_exec_cmd->next;
	}
	wait_for_children(i);
	return (TRUE);
}
