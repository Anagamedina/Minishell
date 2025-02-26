/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/25 19:07:55 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cases_builtins(t_mini* mini, t_cmd* curr_cmd)
{
	int	exit_status;

	exit_status = -1;
	if (ft_strcmp(curr_cmd->cmd, "pwd") == 0)
		exit_status = ft_pwd(mini);
	else if (ft_strcmp(curr_cmd->cmd, "echo") == 0)
		exit_status = ft_echo(curr_cmd, mini);
	else if (ft_strcmp(curr_cmd->cmd, "export") == 0)
	{
		if (curr_cmd->cmd_args[1])
			exit_status = ft_export(curr_cmd, mini);
		else
		{
			print_export(&mini->env);
			exit_status = 0;
		}
	}
	else if (ft_strcmp(curr_cmd->cmd, "unset") == 0)
		exit_status = ft_unset(&(mini->env), curr_cmd);
	else if (ft_strcmp(curr_cmd->cmd, "env") == 0)
		exit_status = ft_env(mini->env);
	else if (ft_strcmp(curr_cmd->cmd, "cd") == 0)
		exit_status = ft_cd(mini, curr_cmd);
	else if (ft_strcmp(curr_cmd->cmd, "exit") == 0)
	{
		exit_status = builtin_exit(curr_cmd, mini);
		if (exit_status == 255 || exit_status == 0)
			cleanup_and_exit(mini, exit_status);
	}
	return (exit_status);
}
