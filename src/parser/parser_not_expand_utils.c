/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_not_expand_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:32:22 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/20 00:13:04 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

	/**
     * Case 2: Dollar sign followed by a single-quoted string.
     * - Ensures `$` inside single quotes does not expand.
     * - Delegates processing to handle_single_quotes_after_dollar.
     *
     * @example:
     * Input: "echo $'hello'"
     * Output: "$'hello'" (no expansion).
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


/**
 * Case 1: Backslash before dollar sign.
 * - Skips expansion when `$` is escaped with `\`.
 * - Delegates processing to handle_backslash_after_dollar.
 *
 * @example
 * Input: "echo \\$USER"
 * Output: "\\$USER" (unexpanded, backslash preserved).
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

/**
 * Case 3: Dollar sign followed by a single digit.
 * - Handles cases where `$` is immediately followed by a digit.
 * - Delegates processing to handle_one_digit_after_dollar.
 *
 * Example:
 * Input: "echo $1"
 * Output: "value_of_argument_1"(if positional parameter expansion is supported).
 */

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

/**
 * Case 4: Dollar sign followed by a digit and more characters.
 * - Handles patterns like `$1extra`.
 * - Delegates processing to handle_digit_and_more_after_dollar.
 *
 * Example:
 * Input: "echo $1abc"
 * Output: "value_of_argument_1abc" (if expansion and concatenation are supported).
 * TODO: agregar una validacion de que solamente cuando existe un dolar en el string return TRUE
 */

int	has_dollar_followed_by_digit(const char *str)
{
	int	i;
	int	count_dollar;

	i = 0;
	count_dollar = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			count_dollar ++;
		i ++;
	}
	if (count_dollar > 1)
		return (FALSE);
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


