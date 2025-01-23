/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_not_expand.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:32:22 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/23 17:08:51 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_dollar_and_next_token(char** str, t_tokens* next_token)
{
	int	len_str;

	if (next_token == NULL)
		return (FALSE);
	printf("next token: %s\n", next_token->str);
	len_str = (int)ft_strlen(*str);
	if (len_str == 1 && (*str)[0] == '$' && handle_single_quote(next_token) == TRUE)
	{
		free(*str);
		*str = ft_strdup("");
		if (!*str)
		{
			perror("Error: ft_strdup failed");
			return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}




int	check_backslash_before_dollar(const char* str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DOLLAR_SIGN)
		{
			if (i > 0 && str[i - 1] == BACKSLASH)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
int	has_only_one_digit_after_dollar(const char* str)
{
	int	len;

	len = (int)ft_strlen(str);
	return (len == 2 && str[0] == DOLLAR_SIGN \
		&& str[1] >= '0' && str[1] <= '9');
}


int	has_dollar_followed_by_digit(const char* str)
{
	int	i;
	int	count_dollar;

	i = 0;
	count_dollar = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			count_dollar++;
		i++;
	}
	if (count_dollar > 1)
		return (FALSE);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (ft_isdigit(str[i + 1]) == TRUE)
			{
				return (TRUE);
			}
		}
		i++;
	}
	return (FALSE);

}


int	handle_no_expand_cases(t_tokens* token, t_tokens* next_token)
{
	if (check_backslash_before_dollar(token->str))
	{
		return (handle_backslash_after_dollar(token));
	}

	if (check_dollar_and_next_token(&token->str, next_token))
	{
		return (handle_single_quotes_after_dollar(next_token));
	}

	if (has_only_one_digit_after_dollar(token->str))
		return (handle_one_digit_after_dollar(token));

	if (has_dollar_followed_by_digit(token->str))
		return (handle_digit_and_more_after_dollar(token));

	// if (has_dollar_with_only_spaces_or_only_dollar(token->str))
	// 	return (handle_dollar_with_space_single(token));
	return (0);
}
