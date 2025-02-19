/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/19 12:50:31 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void setup_fds(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
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

void handle_child(t_cmd *curr_cmd, t_mini *mini)
{

	heredoc(curr_cmd);
	if (apply_redirections(curr_cmd) > 0)
	{
		if (curr_cmd->input_fd != STDIN_FILENO)
		    redirect_in(curr_cmd->input_fd);
		if (curr_cmd->output_fd!= STDOUT_FILENO)
		    redirect_out(curr_cmd->output_fd);
	}
	else //PIPE
	{
		if (curr_cmd->output_fd != STDOUT_FILENO)
		    redirect_out(curr_cmd->output_fd);
		if (curr_cmd->input_fd != STDIN_FILENO)
		    redirect_in(curr_cmd->input_fd);
	}
	execute_builtin_or_external(curr_cmd, mini);
}



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
		close(pipe_fd[0]);
}

static void wait_for_children(int num_children)
{
	while (num_children > 0)
	{
		if (wait(NULL) == -1)
			perror("Error esperando proceso hijo");
		else
			num_children--;
	}
}
//***************************************************************************/
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

		if (curr_cmd->is_builtin == 1 && curr_cmd->next == NULL)
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