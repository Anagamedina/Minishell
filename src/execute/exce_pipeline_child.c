/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_pipeline_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:05:02 by catalinab         #+#    #+#             */
/*   Updated: 2025/03/11 18:53:16 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	apply_and_redirect(t_cmd *curr_cmd, int *pipe_fd)
{
	if (apply_redirections(curr_cmd) > 0)
	{
		if (curr_cmd->input_fd != STDIN_FILENO)
		{
			redirect_in(curr_cmd->input_fd);
			if (pipe_fd[1] >= 0)
				close(pipe_fd[1]);
		}
		if (curr_cmd->output_fd != STDOUT_FILENO)
		{
			redirect_out(curr_cmd->output_fd);
			if (pipe_fd[0] >= 0)
				close(pipe_fd[0]);
		}
	}
	else
	{
		if (curr_cmd->output_fd != STDOUT_FILENO)
			redirect_out(curr_cmd->output_fd);
		if (curr_cmd->input_fd != STDIN_FILENO)
			redirect_in(curr_cmd->input_fd);
	}
}

static void	close_unused_pipes(int *pipe_fd)
{
	if (pipe_fd[0] >= 0)
		close(pipe_fd[0]);
	if (pipe_fd[1] >= 0)
		close(pipe_fd[1]);
}

void	handle_child(t_cmd *curr_cmd, t_mini *mini, int *pipe_fd)
{
	heredoc(curr_cmd);
	apply_and_redirect(curr_cmd, pipe_fd);
	close_unused_pipes(pipe_fd);
	execute_builtin_or_external(curr_cmd, mini);
}
