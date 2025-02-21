/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:11:54 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/21 18:52:42 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//TODO: ver si se puede usar mini->envp_to_array
void	execute_external(t_cmd *cmd, char **envp)
{
	int 	err_excec;
	
	//set_signals(CHILD);
	err_excec = execve(cmd->cmd_path, cmd->cmd_args, envp);
	if (err_excec == -1)
	{
		perror("Error ejecutando comando externo con execve");
		//ft_msgs(0, cmd->cmd);
		exit(127);
	}
	//exit(EXIT_FAILURE);
	exit(0);
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

void	execute_builtin_or_external(t_cmd *curr_cmd, t_mini *mini)
{
	if (curr_cmd->is_builtin == 1)
	{
		cases_builtins(mini, curr_cmd);
		exit(0);
	}
	if (curr_cmd->is_external == 1)
	{
		execute_external(curr_cmd, mini->envp_to_array);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}
