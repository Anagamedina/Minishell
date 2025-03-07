/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 16:45:04 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_out_builtin(t_cmd *cmd, int *saved_stdout)
{
	*saved_stdout = -1;
	if (cmd->output_fd == STDOUT_FILENO)
		return (TRUE);
	if (cmd->output_fd == -1)
	{
		write(2, "Error: Archivo no válido para redirección\n", 42);
		return (FALSE);
	}
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		write(2, "Error guardando stdout\n", 23);
		return (FALSE);
	}
	if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
	{
		write(2, "Error redirigiendo salida\n", 26);
		return (FALSE);
	}
	close(cmd->output_fd);
	return (TRUE);
}

int	pre_executor(t_mini *mini, t_cmd *cmd)
{
	int	saved_stdout;

	saved_stdout = -1;
	if (cmd->has_pipe == TRUE || !is_builtin_command(cmd->cmd))
		return (FALSE);
	if (!cmd->redir_list)
	{
		mini->exit_status = cases_builtins(mini, cmd);
		return (TRUE);
	}
	if (apply_redirections(cmd) == -1)
		return (FALSE);
	if (!redirect_out_builtin(cmd, &saved_stdout))
		return (FALSE);
	mini->exit_status = cases_builtins(mini, cmd);
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	return (TRUE);
}

int	execute_builtin_if_needed(t_mini *mini, t_cmd *cmd, t_list **cmd_list)
{
	if (cmd->is_builtin == 1 && (*cmd_list)->next == NULL)
	{
		if (pre_executor(mini, cmd) == TRUE)
		{
			*cmd_list = (*cmd_list)->next;
			return (TRUE);
		}
	}
	return (FALSE);
}

int	execute_commands(t_mini *mini)
{
	t_list	*t_list_exec_cmd;
	t_cmd	*curr_cmd;
	int		input_fd;
	int		pipe_fd[2] = {-1, -1};
	int		i;

	i = 0;
	input_fd = STDIN_FILENO;
	t_list_exec_cmd = mini->exec->first_cmd;
	while (t_list_exec_cmd)
	{
		curr_cmd = (t_cmd *)t_list_exec_cmd->content;
		curr_cmd->cmd_id = i++;
		if (execute_builtin_if_needed(mini, curr_cmd, &t_list_exec_cmd))
			continue ;
		setup_fds(curr_cmd, pipe_fd, &input_fd);
		fork_and_execute(curr_cmd, mini, pipe_fd, &input_fd);
		t_list_exec_cmd = t_list_exec_cmd->next;
	}
	wait_children(mini);
	mini->exec->is_running = 0;
	return (TRUE);
}
