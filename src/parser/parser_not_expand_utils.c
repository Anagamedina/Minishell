/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_not_expand_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:32:22 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/17 22:08:02 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * check if the next character is a single quote like $'hello
 * echo "$'USER'"
 */

int	check_dollar_and_next_token(char** str, t_tokens* next_token)
{
	int	len_str;

	if (next_token == NULL)
		return (FALSE);
	printf("next token: %s\n", next_token->str);
	len_str = (int) ft_strlen(*str);
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
/*
int	check_d_quote_dollar_s_quote(const char *str)
{
	int	i;
	int	len_str;

	i = 0;
	len_str = (int) ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i ++;
			if (str[i] == S_QUOTE && str[len_str - 2] == S_QUOTE)
				return (TRUE);
		}
		i++;
	}
	return (0);
}
*/

int	check_backslash_before_dollar(const char *str)
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

int	has_only_one_digit_after_dollar(const char *str)
{
	int	len;

	len = (int) ft_strlen(str);
	return (len == 2 && str[0] == DOLLAR_SIGN \
		&& str[1] >= '0' && str[1] <= '9');
}

/**
 * Checks if the token starts with `$` followed by a digit
 * and additional characters.
 */

int	has_dollar_followed_by_digit(const char *str)
{
	int	i;

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

int	calculate_result_size(const char *str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == BACKSLASH && str[i + 1])
			i ++;
		len++;
		i++;
	}
	return (len);
}

void	process_string(const char *str, char *result)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == BACKSLASH && str[i + 1])
		{
			if (str[i + 1] == 'n')
				result[j++] = '\n';
			else if (str[i + 1] == 't')
				result[j++] = '\t';
			else
				result[j++] = str[i + 1];
			i += 2;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
}


//echo "$'\n..\t'"-> $'USER'
char	*convert_escape_sequences(const char *str)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = calculate_result_size(str);
	result = malloc(len + 1);
	if (!result)
	{
		perror("malloc error");
		return (NULL);
	}
	process_string(str, result);
	return (result);
}
/**
 * Checks if there is a valid alphabetical character
 * (A-Z or a-z) immediately before the first
 * occurrence of a dollar sign ('$') in the string.
 *
 * @example
 * Input: "Hello$World"
 * Output: TRUE (1)
 *
 * Input: "123$World"
 * Output: FALSE (0)
 *
 * @return TRUE (1) if there is a valid letter before the dollar sign.
 *         FALSE (0) otherwise.
 */

