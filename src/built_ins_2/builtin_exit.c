/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/23 13:33:19 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}



static void	exit_with_one_argument(t_cmd *cmd, t_mini *mini)
{
	long long	tmp_status;
	
	tmp_status = 0;
	if (!is_numeric(cmd->cmd_args[1]))
	{
		error_exit(mini);
	}
	tmp_status = ft_atoll(cmd->cmd_args[1]);

	if ((cmd->cmd_args[1][0] == '-' && ft_strncmp(&(cmd->cmd_args[1][1]), "9223372036854775808", 19) > 0) ||
		(cmd->cmd_args[1][0] != '-' && ft_strncmp(cmd->cmd_args[1], "9223372036854775807", 19) > 0))
	{
		ft_putstr_fd("exit\nminishell: exit: numeric argument required\n", 2);
		cleanup_and_exit(mini, 255);
	}
	mini->exit_status = (unsigned char) tmp_status;
	cleanup_and_exit(mini, mini->exit_status);
}

int	builtin_exit(t_cmd* cmd, t_mini* mini)
{
	int	arg_count;

	arg_count = 0;
	while (cmd->cmd_args[arg_count] != NULL)
		arg_count ++;	
	if (arg_count == 1)
		cleanup_and_exit(mini ,mini->exit_status);
	if (arg_count == 2)
	{
		exit_with_one_argument(cmd, mini);
	}
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	mini->exit_status = 1;
	return (1);
}
