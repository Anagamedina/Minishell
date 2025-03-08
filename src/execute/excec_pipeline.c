/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excec_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:05:02 by catalinab         #+#    #+#             */
/*   Updated: 2025/03/09 00:20:17 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_fds(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
	if (!curr_cmd->last_cmd)
	{
		curr_cmd->has_pipe = 1;
		if (pipe(pipe_fd) == -1)
		{
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

void	wait_children(t_mini *mini)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
}

void	handle_child(t_cmd *curr_cmd, t_mini *mini, int *pipe_fd)
{
	heredoc(curr_cmd);
	if (apply_redirections(curr_cmd) > 0)
	{
		if (curr_cmd->input_fd != STDIN_FILENO)
		{
			redirect_in(curr_cmd->input_fd);
			close(pipe_fd[1]);

		}
		if (curr_cmd->output_fd != STDOUT_FILENO)
		{
			redirect_out(curr_cmd->output_fd);
			close(pipe_fd[0]);
		}
	}
	else
	{
		if (curr_cmd->output_fd != STDOUT_FILENO)
			redirect_out (curr_cmd->output_fd);
		if (curr_cmd->input_fd != STDIN_FILENO)
			redirect_in(curr_cmd->input_fd);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	execute_builtin_or_external(curr_cmd, mini);
}



void	handle_parent(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
	if (curr_cmd->input_fd != STDIN_FILENO && curr_cmd->input_fd >= 0)
		close(curr_cmd->input_fd);
	if (curr_cmd->output_fd != STDOUT_FILENO && curr_cmd->output_fd >= 0)
		close(curr_cmd->output_fd);
	if (!curr_cmd->last_cmd)
	{
		if (pipe_fd[1] >= 0)
			close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	else
	{
		if (pipe_fd[0] >= 0)
			close(pipe_fd[0]);
	}
}

void	fork_and_execute(t_cmd *cmd, t_mini *mini, \
		int pipe_fd[2], int *input_fd)
{
	pid_t	pid;
	printf("El PID del PADRE es: %d\n", getpid());

	pid = fork();
	if (pid < 0)
	{
		free_mini(mini);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		printf("El PID del HIJO es: %d\n", getpid());
		setup_signals(CHILD);
		handle_child(cmd, mini, pipe_fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		handle_parent(cmd, pipe_fd, input_fd);
	}
}
