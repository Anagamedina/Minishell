/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 18:55:34 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO: free env list
void	cleanup_and_exit(t_mini* mini, int status)
{
	// free_env_list(mini->env);
	free_exec(mini->exec);
	free_mini(mini);
	exit(status);
}

static long long 	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	long long	prev_result;

	i = 0;
	sign = 1;
	result = 0;
	prev_result = 0;
	while (str[i] >= 9 && str[i] <= 13)
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev_result = result;
		result = (result * 10) + (str[i] - '0');
		if ((sign == 1 && result < prev_result) || (sign == -1 && result < prev_result))
		{
			if (sign == 1)
				return (ft_atoll(MY_LLONG_MAX));
			else
				return (ft_atoll(MY_LLONG_MIN));
		}
		i++;
	}
	return (result * sign);
}

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

void	error_exit(t_mini *mini)
{
	ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	cleanup_and_exit(mini, 255);
}

/**
 * Implement three cases:
 * 
 * 1. exit without arguments
 * 2. exit with a numeric argument
 * 3. exit with a non-numeric argument
 */

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
