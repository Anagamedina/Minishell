/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/19 17:26:30 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(int status)
{
	exit(status);
}

/**
 * Implement three cases:
 * 
 * 1. exit without arguments
 * 2. exit with a numeric argument
 * 3. exit with a non-numeric argument
 */

// static void	exit_with_one_argument(t_cmd *cmd, int *last_status)
static void	exit_with_one_argument(t_cmd *cmd, t_mini *mini)
{
	int	i;

	i = 0;
	while (cmd->cmd_args[1][i])
	{
		if (!ft_isdigit(cmd->cmd_args[1][i]))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(cmd->cmd_args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			mini->exit_status = 255;
			ft_exit(255);
		}
		i ++;
	}
	mini->exit_status = ft_atoi(cmd->cmd_args[1]);
}

void	builtin_exit(t_cmd *cmd, t_mini *mini)
{
	if (cmd->cmd_args[2] != NULL)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		ft_exit(1);
	}
	else if (cmd->cmd_args[1])
	{
		exit_with_one_argument(cmd, mini);
	}

	ft_putstr_fd("exit\n", 1);
	ft_exit(mini->exit_status);
}


		// i = 0;
		// while (cmd->cmd_args[1][i])
		// {
		// 	if (!ft_isdigit(cmd->cmd_args[1][i]))
		// 	{
		// 		ft_putstr_fd("exit\nminishell: exit: ", 2);
		// 		ft_putstr_fd(cmd->cmd_args[1], 2);
		// 		ft_putstr_fd(": numeric argument required\n", 2);
		// 		ft_exit(255);
		// 	}
		// 	i ++;
		// }