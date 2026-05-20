/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/14 17:38:14 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i ++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_out_of_llong_range(char *str)
{
	int	len;

	while (*str == '0')
		str++;
	len = (int) ft_strlen(str);
	if (len > 19)
		return (1);
	if (len == 19)
	{
		if (str[0] == '-')
		{
			if (ft_strncmp(str + 1, "9223372036854775808", 19) > 0)
				return (1);
		}
		else
		{
			if (ft_strncmp(str, "9223372036854775807", 19) > 0)
				return (1);
		}
	}
	return (0);
}

int	builtin_exit(t_cmd *cmd, t_mini *mini)
{
	int	arg_count;

	arg_count = 0;
	while (cmd->cmd_args[arg_count] != NULL)
		arg_count++;
	if (arg_count == 1)
		cleanup_and_exit(mini, mini->exit_status);
	if (!is_numeric(cmd->cmd_args[1]) || is_out_of_llong_range(cmd->cmd_args[1]))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->cmd_args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		cleanup_and_exit(mini, 2);
	}
	if (arg_count > 2)
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		mini->exit_status = 1;
		return (1);
	}
	mini->exit_status = (unsigned char)ft_atoll(cmd->cmd_args[1]);
	ft_putendl_fd("exit", 2);
	cleanup_and_exit(mini, mini->exit_status);
	return (0);
}
