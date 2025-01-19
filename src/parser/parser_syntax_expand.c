/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:16:05 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/20 00:21:25 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//----> \$USER
static int	handle_backslash_after_dollar(t_tokens *token)
{
	char	*temp;

	temp = remove_quotes_str(token->str, D_QUOTE);
	token->str = ft_strdup(temp + 1);
	if (!token->str)
	{
		perror("error: ft_strdup failed");
		return (FALSE);
	}
	return (TRUE);
}

// caso $'..'---> \t ... SIN COMILLA DOBLES
// TODO: rename function
static int	handle_single_quotes_after_dollar(t_tokens *token)
{
	char	*temp;
	char	*processed_str;

	processed_str = remove_quotes_str(token->str, S_QUOTE);
	if (!processed_str)
	{
		perror("Error: remove_quotes_str failed");
		return (FALSE);
	}
	temp = convert_escape_sequences(processed_str);

	if (!temp)
	{
		perror("Error: convert_escape_sequences failed");
		return (FALSE);
	}
	free(token->str);
	token->str = ft_strdup(temp);
	if (!token->str)
	{
		perror("Error: ft_strdup failed");
		return (FALSE);
	}
	return (TRUE);
}

/*
static int	handle_single_quotes_after_dollar(t_tokens *token)
{
	char	*temp;

	temp = convert_escape_sequences(token->str + 1);
	free(token->str);
	token->str = ft_strdup(remove_quotes_str(temp, D_QUOTE));//doble???
	if (!token->str)
	{
		perror("error: ft_strdup failed");
		return (FALSE);
	}
	return (TRUE);
}
*/
static int	handle_one_digit_after_dollar(t_tokens *token)
{
	token->str = ft_strdup("");
	return (TRUE);
}

/**
 * Trims the token's string to only include
 * the part before the first '$' character.
 *
 * @token The token containing the string to process.
 *
 * Steps:
 * 1. Removes double quotes (`"`) from the string.
 * 2. Extracts the substring before the first '$'.
 * 3. Updates the token with the processed string.
 *
 * Example:
 * Input: token->str = "\"Hello $World\"";
 * Output: token->str = "Hello ".
 *
 * Returns:
 * - TRUE (1) on success.
 * - FALSE (0) if memory allocation fails.
 */

static int	handle_str_trim_before_dollar(t_tokens *token)
{
	char	*temp;
	char	*substring_str;
	char	*dollar_pos;

	temp = remove_quotes_str(token->str, D_QUOTE);
	if (!temp)
	{
		perror("error: remove_quotes_str failed");
		return (FALSE);
	}
	free(token->str);
	token->str = ft_strdup(temp);
	free(temp);

	printf("token->str: [%s]\n", token->str);

	dollar_pos = ft_strchr(token->str, DOLLAR_SIGN);
	if (dollar_pos)
	{
		substring_str = ft_substr(token->str, 0, dollar_pos - token->str);
		printf("substring_str: [%s]\n", substring_str);
		if (!substring_str)
		{
			perror("Error: ft_substr failed");
			free(token->str);
			return (FALSE);
		}
		free(token->str);
		token->str = ft_strdup(substring_str);
		free(substring_str);
	}
	printf("token->str after trim: [%s]\n", token->str);
	return (TRUE);
}


//  TODO: En el siguiente caso echo "$USER abcdh $HOME $1" falta eliminar $1.

static int	handle_digit_and_more_after_dollar(t_tokens *token)
{
	char	*temp;

	if (token->str[0] == D_QUOTE && token->str[token->length - 1] == D_QUOTE)
	{
		temp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(temp);
		temp = NULL;
	}
	temp = ft_strdup(token->str + 2);
	if (!temp)
	{
		perror("error: strdup");
		exit(EXIT_FAILURE);
	}
	free(token->str);
	token->str = temp;
	return (TRUE);
}


//caso--> "'$'"
/*
static int	check_dollar_special_quote(const char *str)
{
	if (ft_strchr_true(str, DOLLAR_SIGN) \
		&& ft_strchr_true(str, D_QUOTE) && ft_strchr_true(str, S_QUOTE))
		return (TRUE);
	return (FALSE);
}
*/

int	has_dollar_with_only_spaces_or_only_dollar(const char* str)
{
	return (
		(str[0] != '\0' && str[0] == '"' && str[1] != '\0' && str[1] == '$' \
		&& str[2] != '\0' && str[2] == ' ') || \
		(str[0] != '\0' && str[0] == '"' && str[1] != '\0' && str[1] == '$'));
}

/*
int handle_dollar_with_space_single(t_tokens* token)
{
	char	*temp;

	if (token->str[0] == D_QUOTE && token->str[token->length - 1] == D_QUOTE)
	{
		temp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(temp);
		temp = NULL;
	}
	return (TRUE);
}
*/


// Caso "$ '...'" -> manejar espacio después del dólar

int	check_dquote_dollar_and_squotes(const char *str)
{
	int i;
	int len_str;

	i = 0;
	len_str = (int) ft_strlen(str);

	while (str[i] != '\0')
	{
		if (str[i] == DOLLAR_SIGN)
		{
			i++;
			while (str[i] == ' ')
				i++;
			if (str[i] == S_QUOTE && str[len_str - 2] == S_QUOTE)
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	handle_dollar_with_space_single(t_tokens *token)
{
	char	*temp;

	temp = remove_quotes_str(token->str, D_QUOTE);
	token->str = ft_strdup(temp);
	free(temp);
	if (!token->str)
	{
		perror("error: ft_strdup failed");
		return (FALSE);
	}
	return (TRUE);
}

//echo $'USER'
//USER
int	check_dollar_simple(char *str)
{
	int i;
	int len_str;

	i = 0;
	len_str = (int) ft_strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == S_QUOTE && str[len_str - 1] == S_QUOTE)
				return (TRUE);
		}
		i++;
	}
	return (0);
}


/**
 * TODO: daruny(finish this function)
 * d_quote -> s_quote -> (string o $)
 *
 * Case: "'$...'"
 * this 3 cases are valid:
 * " ' $USER ' "
 * ""' $USER ' ""
 * " " " ' $USER ' " " "
 */

int	check_dquote_squote_dollar_case(char *str)
{
	int	i;
	int	len_str;
	int	condition1;
	int	condition2;
	char	tmp;

	condition1 = FALSE;
	condition2 = FALSE;
	len_str = (int) ft_strlen(str);

	if (str[0] != D_QUOTE || str[len_str - 1] != D_QUOTE)
		return (FALSE);
	i = 1;

	while (i < len_str - 1)
	{
		tmp = str[i];

		while (str[i] == ' ' && i < len_str - 1)
			i ++;
		if (str[i] == S_QUOTE)
			condition1 = TRUE;

		//posible error here with case: echo " ' $USER  ' "
		if (str[i] == DOLLAR_SIGN && (i + 1) < len_str - 1 \
			&& str[i + 1] != ' ' && str[i + 1] != '\0')
			condition2 = TRUE;
		if (condition1 && condition2)
			return (TRUE);
		i ++;
	}
	return (FALSE);
}

/************ MAIN FUNCTION *************/

/**
 * Expands dollar variables in a token based on specific cases.
 *
 * @param token Current token to process.
 * @param env_list List of environment variables.
 * @param next_token Next token for contextual processing (if needed).
 *
 * Cases handled:
 * 1. Mixed single and double quotes with `$`.
 * 2. Variable expansion inside double quotes, skipping single quotes.
 * 3. Tokens with no variable expansion required.
 * 4. General dollar variable expansion.
 */

void	handle_dollar_cases(t_tokens *token, t_list *env_list, t_tokens* next_token)
{
	char	*processed_str;
	char	*expanded_str;

	processed_str = NULL;
	expanded_str = NULL;

	/**
	 * Handles cases with mixed d_quotes (") and s_quotes (') containing `$`.
	 *
	 * - Ensures only one valid pair of double quotes exists (open and close).
	 * - Allows spaces between double and single quotes.
	 * - Invalidates consecutive dollar signs (`$$`).
	 * @example:
	 * Input: `"$'string'"` or `" $ 'string'"`.
	 * Output: Processed token without expanding variables inside single quotes.
	 */

	if (check_dquote_dollar_and_squotes(token->str))
	{
		handle_dollar_with_space_single(token);
		return ;
	}

	/**
	 * Expands variables within double quotes, preserving single quotes.
	 *
	 * Key points:
	 * - Removes outer double quotes before processing.
	 * - Expands variables inside d_quotes while skipping single-quoted parts.
	 * @example
	 * Input: `"'$USER'"`.
	 * Output: `"'daruu'"` (assuming `$USER=daruu`).
	 */

	if (check_dquote_squote_dollar_case(token->str))
	{
		printf("original str: [%s]\n", token->str);

		processed_str = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(processed_str);
		printf("after remove_quotes_str: [%s]\n", token->str);

		expanded_str = \
		replace_dollar_variable_skip_s_quote(token->str, env_list);
		free(token->str);
		token->str = ft_strdup(expanded_str);
		printf("after replace_dollar_variable : [%s]\n", token->str);

		free(processed_str);
		return ;
	}

	/**
	 * Handles tokens that do not require variable expansion.
	 * Key points:
	 * - Leaves tokens unchanged when they contain no expandable variables.
	 * - Typically for pure strings or escaped quotes.
	 *
	 * @example
	 * Input: `'string'` or `\"escaped\"`.
	 * Output: Unchanged token value.
	 */
	if (handle_no_expand_cases(token, next_token) == 0)
	{
		expand_dollar(token, env_list);
		return ;
	}
}

/**
 * Handles tokens where dollar-based expansion is conditional or restricted.
 *
 * This function checks for specific patterns
 * involving the `$` character in the token string
 *
 * @return
 * - TRUE if a specific case is handled.
 * - FALSE if no matching condition is found.
 */

int	handle_no_expand_cases(t_tokens *token, t_tokens* next_token)
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
/*
	 remove this case to see whats happening
	 caso a gestionar TODO: echo "$USER abcdh $HOME $1"
*/
	if (has_dollar_followed_by_digit(token->str))
		return (handle_digit_and_more_after_dollar(token));
	/*
	 if (has_dollar_with_only_spaces_or_only_dollar(token->str))
		return (handle_dollar_with_space_single(token));
	 */
	return (0);
}
