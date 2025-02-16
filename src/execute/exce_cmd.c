/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/16 18:16:07 by dasalaza         ###   ########.fr       */
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
	if (!curr_cmd->last_cmd)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Error creando pipe");
			exit(EXIT_FAILURE);
		}
		curr_cmd->output_fd = pipe_fd[1];
	}
	else
	{
		curr_cmd->output_fd = STDOUT_FILENO; // Último comando: salida a STDOUT
	}

	curr_cmd->input_fd = *input_fd;
}



void redirect_open(int input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("Error redirigiendo entrada");
		exit(EXIT_FAILURE);
	}
	close(input_fd);
}

void redirect_close(int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirigiendo salida a archivo");
		exit(EXIT_FAILURE);
	}
	close(output_fd);
}


void handle_child(t_cmd *curr_cmd, t_mini *mini)
{
	char	**envp_to_array;


	// print_list_commands(mini->exec->first_cmd);
	heredoc(curr_cmd);
	if (apply_redirections(curr_cmd) > 0)
	{
		if (curr_cmd->input_fd != STDIN_FILENO)
		    redirect_open(curr_cmd->input_fd);
		if (curr_cmd->output_fd!= STDOUT_FILENO)
		    redirect_close(curr_cmd->output_fd);
	}
	else //PIPE
	{
		if (curr_cmd->output_fd != STDOUT_FILENO)
		    redirect_close(curr_cmd->output_fd);
		if (curr_cmd->input_fd != STDIN_FILENO)
		    redirect_open(curr_cmd->input_fd);
	}
	envp_to_array = lst_to_arr(mini->env);
	if (curr_cmd->is_external == 1)
		execute_external(curr_cmd, envp_to_array);
	else if (curr_cmd->is_builtin == 1)
		cases_builtins(mini);
	exit(EXIT_FAILURE);
}



/*
static void handle_parent(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
	// Cerrar el extremo de escritura en el padre si no es el último comando
	if (curr_cmd->output_fd != STDOUT_FILENO)
	{
		close(curr_cmd->output_fd);
		// close(pipe_fd[1]);
	}

	// Cerrar el extremo de lectura anterior si no es STDIN
	if (curr_cmd->input_fd != STDIN_FILENO)
	{
		close(curr_cmd->input_fd);
	}

	// Actualizar `input_fd` para el siguiente comando
	*input_fd = pipe_fd[0];
}*/
static void handle_parent(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
	if (curr_cmd->input_fd != STDIN_FILENO)
		close(curr_cmd->input_fd);
	if (curr_cmd->output_fd != STDOUT_FILENO)
		close(curr_cmd->output_fd);

	if (!curr_cmd->last_cmd)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	else
	{
		close(pipe_fd[0]);
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
	t_list *t_list_exec_cmd = mini->exec->first_cmd;
	t_cmd  *curr_cmd;
	pid_t  pid;
	int    input_fd = STDIN_FILENO;
	int    pipe_fd[2];
	int    i = 0;

	while (t_list_exec_cmd)
	{
		curr_cmd = (t_cmd *)t_list_exec_cmd->content;
		curr_cmd->cmd_id = i++;
		// 🔹 1️⃣ **Procesar todos los heredocs antes de ejecutar comandos**
		/*t_list *temp_cmd = t_list_exec_cmd;
		while (temp_cmd)
		{
			curr_cmd = (t_cmd *)temp_cmd->content;
			heredoc(curr_cmd);  // 👈 Llamamos a heredoc antes de ejecutar
			temp_cmd = temp_cmd->next;
		}*/
	//	heredoc(curr_cmd);
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