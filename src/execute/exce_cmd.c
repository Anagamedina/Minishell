/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/24 17:44:23 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_fds(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
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
		curr_cmd->output_fd = STDOUT_FILENO;
	}
	curr_cmd->input_fd = *input_fd;
}

void	handle_child(t_cmd *curr_cmd, t_mini *mini)
{
	heredoc(curr_cmd);
	if (apply_redirections(curr_cmd) > 0)
	{
		if (curr_cmd->input_fd != STDIN_FILENO)
			redirect_in(curr_cmd->input_fd);
		if (curr_cmd->output_fd != STDOUT_FILENO)
			redirect_out(curr_cmd->output_fd);
	}
	else
	{
		if (curr_cmd->output_fd != STDOUT_FILENO)
			redirect_out (curr_cmd->output_fd);
		if (curr_cmd->input_fd != STDIN_FILENO)
			redirect_in(curr_cmd->input_fd);
	}
	execute_builtin_or_external(curr_cmd, mini);
}

static void	handle_parent(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
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
		close(pipe_fd[0]);
}

int	execute_commands(t_mini *mini)
{
	t_list	*t_list_exec_cmd;
	t_cmd	*curr_cmd;
	pid_t	pid;
	int		input_fd;
	int		pipe_fd[2];
	int		i;
	int		status;

	i = 0;
	input_fd = STDIN_FILENO;
	t_list_exec_cmd = mini->exec->first_cmd;
	while (t_list_exec_cmd)
	{
		curr_cmd = (t_cmd *)t_list_exec_cmd->content;
		curr_cmd->cmd_id = i++;

		// caso no works: echo "hello" > file.txt que no funciona bien
		if (curr_cmd->is_builtin == 1 && t_list_exec_cmd->next == NULL)
		{
			cases_builtins(mini, curr_cmd);
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
			//printf("Mi PID hijo es: %d\n", getpid());
			exit(EXIT_SUCCESS);
		}
		else
		{
			handle_parent(curr_cmd, pipe_fd, &input_fd);
			//printf("Mi PID padre es: %d\n", getpid());
		}
		t_list_exec_cmd = t_list_exec_cmd->next;
	}

	// wait all children process
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
	}

	return (TRUE);
}

/*
void	set_exit_status(int n)
{
	g_get_signal = n;
}*/