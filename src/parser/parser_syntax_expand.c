//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"

int has_string_before_dollar(char *str);

/**
 * check if the next character is a single quote like $'hello
 * echo "'$USER'"
 */
int	check_dollar_after_single_quote(const char *str)  //$'..'
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
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * check if the previous character is a backslash like \\$hello
 * return TRUE or FALSE
 * echo "\$aaa
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
	int len;

	len = (int) ft_strlen(str);
	return (len == 2 && str[0] == DOLLAR_SIGN \
		&& str[1] >= '0' && str[1] <= '9');
}

/**
 * Checks if the token starts with `$` followed by a digit
 * and additional characters.
 */

int	is_digit_and_more_after_dollar(const char *str)
{
	return (str[0] == '$' && ft_isdigit(str[1]) == 1 && str[2] != '\0');
}

/**
 * Calculates the length of a string after removing $<digit> patterns.
 * @param str Input string.
 * @return Length of the new string.
 */
/*
int	calculate_new_length(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] == '$' && str[i + 1] && ft_isdigit(str[i + 1])))
			len++;
		else
			i++;
		i++;
	}
	return (len);
}
*/

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
	int 	len;

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

int has_string_before_dollar(char *str) {
	int i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DOLLAR_SIGN)
		{
			j = i - 1;
			if ((str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= 'a' && str[j] <= 'z'))
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}
