/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_count_dollar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:42:14 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 20:42:16 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_count_dollar_vars(int *i, int *count_dollar)
{
	*i = 0;
	*count_dollar = 0;
}

static int	count_dollar_occurrences(const char *str)
{
	int	i;
	int	count_dollar;

	init_count_dollar_vars(&i, &count_dollar);
	while (str[i] != '\0')
	{
		while (str[i] == SPACE)
			i++;
		if (str[i] == DOLLAR_SIGN && \
				(ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			count_dollar++;
			i++;
			while (str[i] != '\0' && (ft_isalpha(str[i]) || str[i] == '_'))
				i++;
		}
		else if (str[i] == DOLLAR_SIGN && str[i + 1] == ' ')
		{
			count_dollar++;
			i++;
		}
		else
			i++;
	}
	return (count_dollar);
}

int	has_consecutives_env_variables_in_token(t_tokens *token)
{
	if (!token || !token->str)
		return (FALSE);
	if (token->str[0] == D_QUOTE)
		return (count_dollar_occurrences(token->str + 1) >= 1);
	return (count_dollar_occurrences(token->str) >= 1);
}
