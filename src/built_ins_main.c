/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:03:47 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/13 19:12:49 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 00:06:05 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	aux_export(t_mini *mini, t_cmd *curr_cmd)
{
	int	exit_status;

	if (curr_cmd->cmd_args && curr_cmd->cmd_args[1])
		exit_status = ft_export(curr_cmd, mini);
	else
	{
		if (mini)
			print_export(&mini->env);
		exit_status = 0;
	}
	return (exit_status);
}

int	cases_builtins(t_mini *mini, t_cmd *curr_cmd)
{
	int	exit_status;

	if (!curr_cmd || !curr_cmd->cmd)
		return (-1);
	exit_status = -1;
	if (ft_strcmp(curr_cmd->cmd, "pwd") == 0)
		exit_status = ft_pwd(mini);
	else if (ft_strcmp(curr_cmd->cmd, "echo") == 0)
		exit_status = ft_echo(curr_cmd, mini);
	else if (ft_strcmp(curr_cmd->cmd, "export") == 0)
		exit_status = aux_export(mini, curr_cmd);
	else if (ft_strcmp(curr_cmd->cmd, "unset") == 0)
		exit_status = ft_unset(&(mini->env), curr_cmd);
	else if (ft_strcmp(curr_cmd->cmd, "env") == 0)
	{
		if (curr_cmd->cmd_args && curr_cmd->cmd_args[1] == NULL)
			exit_status = ft_env(mini->env);
		else
			return (127);
	}
	else if (ft_strcmp(curr_cmd->cmd, "cd") == 0)
		exit_status = ft_cd(mini, curr_cmd);
	else if (ft_strcmp(curr_cmd->cmd, "exit") == 0)
	{
		exit_status = builtin_exit(curr_cmd, mini);
		// cleanup_and_exit(mini, exit_status);
		if (exit_status == 255 || exit_status == 0)
			cleanup_and_exit(mini, exit_status);
	}
	return (exit_status);
}
