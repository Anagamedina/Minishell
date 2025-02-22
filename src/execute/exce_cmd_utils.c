/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:11:54 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/22 21:17:33 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_external(t_cmd *cmd, char **envp)
{
	execve(cmd->cmd_path, cmd->cmd_args, envp);
	perror("Error ejecutando comando externo con execve");
	exit(EXIT_FAILURE);
}

void	redirect_in(int input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("Error redirigiendo entrada");
		exit(EXIT_FAILURE);
	}
	close(input_fd);
}

void	redirect_out(int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("Error redirigiendo salida a archivo");
		exit(EXIT_FAILURE);
	}
	close(output_fd);
}

/*void	execute_builtin_or_external(t_cmd *curr_cmd, t_mini *mini)
{
	if (curr_cmd->is_builtin == 1)
	{
		mini->exit_status = cases_builtins(mini, curr_cmd);
		exit(mini->exit_status);
	}
	if (curr_cmd->is_external == 1)
	{
		execute_external(curr_cmd, mini->envp_to_array);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}
*/

void	execute_builtin_or_external(t_cmd *curr_cmd, t_mini *mini)
{
	int	exit_status_last_command;

	exit_status_last_command = 0;
	if (curr_cmd->is_builtin == 1)
	{
		exit_status_last_command = cases_builtins(mini, curr_cmd);
        mini->exit_status = exit_status_last_command;
        exit(mini->exit_status);
	}
	if (curr_cmd->is_external == 1)
	{
		execute_external(curr_cmd, mini->envp_to_array);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}