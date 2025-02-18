/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/19 00:15:29 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by daruuu on 11/18/24.
//

#include "../includes/minishell.h"

void	ft_exit(int last_status)
{
	// ft_putstr_fd("exit\n", 1);
	exit(last_status);
}

void	builtin_exit(t_mini *mini, t_cmd *cmd)
{
	int		last_status;
	int		i;
	int		j;

	last_status = 0;
	if (cmd->cmd_args[1])
	{
		i = 0;
		while (cmd->cmd_args[1][i])
		{
			if (!ft_isdigit(cmd->cmd_args[1][i]))
			{
				ft_putstr_fd("exit\nminishell: exit: ", 2);
				ft_putstr_fd(cmd->cmd_args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				ft_exit(255);
			}
			i++;
		}
		last_status = ft_atoi(cmd->cmd_args[1]);
		if (cmd->cmd_args[2])
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			ft_exit(1);
		}
	}
	ft_putstr_fd("exit\n", 1);
	ft_exit(last_status);
}
