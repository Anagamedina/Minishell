/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 19:14:18 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:58:03 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 12:42:42 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cases_builtins(t_mini* mini, t_cmd* curr_cmd)
{
	int	exit_status;

	exit_status = -1;
	if (ft_strcmp(curr_cmd->cmd, "pwd") == 0)
	{
		return (ft_pwd(mini));
	}
	if (ft_strcmp(curr_cmd->cmd, "echo") == 0)
	{
		return (ft_echo(curr_cmd, mini));
	}
	if (ft_strcmp(curr_cmd->cmd, "export") == 0)
	{
		if (curr_cmd->cmd_args[1] != NULL)
			return (export_variable(curr_cmd, mini));
		else
		{
			print_export(&mini->env);
			return (0);
		}
	}
	if (ft_strcmp(curr_cmd->cmd, "unset") == 0)
	{
		return (ft_unset(&(mini->env), curr_cmd));
	}
	if (ft_strcmp(curr_cmd->cmd, "env") == 0)
	{
		return (print_env_list(mini->env));
	}
	if (ft_strcmp(curr_cmd->cmd, "cd") == 0)
	{
		return (ft_cd(mini, curr_cmd));
	}
	else if (ft_strcmp(curr_cmd->cmd, "exit") == 0)
	{
		exit_status = builtin_exit(curr_cmd, mini);
		if (exit_status == 255 || exit_status == 1)
		{
			cleanup_and_exit(mini, mini->exit_status);
		}
		return (exit_status);
	}
	return (0);
}