/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:57:25 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/10 00:24:09 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cleanup_and_exit(t_mini *mini, int status)
{
	free_mini(mini);
	rl_clear_history();
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

/*
static long long check_overflow(long long result, long long prev_result, int sign)
{
	if ((sign == 1 && result < prev_result) || (sign == -1 && result < prev_result))
	{
		if (sign == 1)
			return (9223372036854775807);
	}
}
*/

long long	ft_atoll(const char *str)
{
	int			i;
	int			sign;
	long long	result;
	long long	prev_result;

	init_varible_atoll(&sign, &i, &result, &prev_result);
	while (str[i] >= 9 && str[i] <= 13)
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i ++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev_result = result;
		result = (result * 10) + (str[i] - '0');
		if ((sign == 1 && result < prev_result) || \
				(sign == -1 && result < prev_result))
			return (9223372036854775807);
		i ++;
	}
	return (result * sign);
}
