/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:57:25 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/04 11:58:18 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_and_exit(t_mini *mini, int status)
{
	free_mini(mini);
	exit(status);
}

static void	init_varible_atoll(int *sign, int *i, \
		long long *result, long long *prev_result)
{
	*i = 0;
	*sign = 1;
	*result = 0;
	*prev_result = 0;
}

int	process_sign_and_whitespace(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] >= 9 && str[*i] <= 13)
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	long long	prev_result;

	init_varible_atoll(&sign, &i, &result, &prev_result);
	sign = process_sign_and_whitespace(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev_result = result;
		result = (result * 10) + (str[i] - '0');
		if (sign == 1 && result < prev_result)
			return (9223372036854775807);
		if (sign == -1 && result < prev_result)
			return (-9223372036854775807 - 1);
		i++;
	}
	return (result * sign);
}

void	error_exit(t_mini *mini)
{
	ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	cleanup_and_exit(mini, 255);
}
