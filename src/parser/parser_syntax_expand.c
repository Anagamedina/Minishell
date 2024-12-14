//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"

/**
 * Handles special cases of tokens that involve the `$`
 *
 * Processes various scenarios involving `$`:
 * - Escaped `$` within double quotes.
 * - `$` followed by a single quote.
 * - `$` followed by a single digit.
 * - `$` followed by a digit and additional characters.
 * - General environment variable expansion.
 *
 * @param token Pointer to the token being processed.
 * @param env_list Pointer to the list of environment variables.
 *
 * Specific cases:
 * @see check_backslash_before_dollar
 * Verifies if `$` is escaped by a backslash.
 * @see check_dollar_after_single_quote
 * Handles `$` inside single quotes.
 * @see has_only_one_digit_after_dollar
 * Checks for single-digit `$` variables.
 * @see expand_dollar
 * Expands variables that start with `$`.
 */

/************ MAIN FUNCTION *************/
void	handle_dollar_cases(t_tokens *token, t_list *env_list)
{
	char	*temp;

	if (check_backslash_before_dollar(token->str) == 1)
	{
		// echo "\$USER" -> $USER
		temp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(temp + 1);
	}
	else if (check_dollar_after_single_quote(token->str) == 1)
	{
		//	echo $'USER\n'
		//	check this function ??????????????????
		temp = convert_escape_sequences(token->str + 1);
		free(token->str);
		token->str = ft_strdup(remove_quotes_str(temp, S_QUOTE));
	}
	else if (has_only_one_digit_after_dollar(token->str))
	{
		//	$1
		token->str = ft_strdup("");
	}
	else if (has_string_before_dollar(token->str))
	{
		// Nota1: actualizar el atributo size del token
		// Nota2: Limpiar frees
		// print string de antes de dollar
		int i = 0;
		int len = 0;

		temp = remove_quotes_str(token->str, D_QUOTE);
//		if (token->str != NULL)
//		{
//			free(token->str);
//		}
		token->str = ft_strdup(temp);
		if (temp != NULL)
		{
			free(temp);
		}
		while (token->str[i] != '\0' && token->str[i] != DOLLAR_SIGN)
		{
			i++;
		}
		len = i;
		temp = ft_substr(token->str, 0, len);
		if (token->str != NULL)
		{
			free(token->str);
		}
		token->str = ft_strdup(temp);
		if (temp != NULL)
		{
			free(temp);
		}
	}
	else if (is_digit_and_more_after_dollar(token->str))
	{
		//	$1hello
		temp = ft_strdup(token->str + 2);
		free(token->str);
		token->str = ft_strdup(temp);
	}
	else
	{
		expand_dollar(token, env_list);
	}
}
