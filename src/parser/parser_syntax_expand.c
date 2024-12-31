/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:26:47 by catalinab         #+#    #+#             */
/*   Updated: 2024/12/27 15:17:24 by  dasalaza        ###   ########.fr       */
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
static int	handle_single_quotes_after_dollar(t_tokens *token)
{
	char	*temp;

	temp = convert_escape_sequences(token->str + 1);
	free(token->str);
	token->str = ft_strdup(remove_quotes_str(temp, D_QUOTE));
	if (!token->str)
	{
		perror("error: ft_strdup failed");
		return (FALSE);
	}
	return (TRUE);
}

static int	handle_one_digit_after_dollar(t_tokens *token)
{
	token->str = ft_strdup("");
	return (TRUE);
}

static int	handle_string_before_dollar(t_tokens *token)
{
	char	*temp;

	temp = remove_quotes_str(token->str, D_QUOTE);
	token->str = ft_strdup(temp);
	if (!token->str)
	{
		perror("error: ft_strdup failed");
		return (FALSE);
	}
	free (temp);
	temp = ft_substr(token->str, 0, \
	ft_strchr(token->str, DOLLAR_SIGN) - token->str);
	free(token->str);
	token->str = ft_strdup(temp);
	free(temp);
	return (TRUE);
}

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

int	handle_no_expand_cases(t_tokens *token)
{
	if (check_backslash_before_dollar(token->str))
		return (handle_backslash_after_dollar(token));
	if (check_doble_dollar_single(token->str)) //$'..'
		return (handle_single_quotes_after_dollar(token));// es la que cumple las \t
	if (has_only_one_digit_after_dollar(token->str))
		return (handle_one_digit_after_dollar(token));
	if (has_string_before_dollar(token->str))
		return (handle_string_before_dollar(token));
	if (has_dollar_followed_by_digit(token->str))
		return (handle_digit_and_more_after_dollar(token));
	return (0);

}

// Caso "$ '...'" -> manejar espacio después del dólar

int	check_dollar_with_space_single(const char *str)
{
	int i;
	int len_str;

	i = 0;
	len_str = (int) ft_strlen(str);

	while (str[i] != '\0')
	{
		if (str[i] == '$')
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

static int	handle_dollar_with_space_single(t_tokens *token)
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

//	TODO: daruny(finish this function)
/**
 * d_quote -> s_quote -> (string o $)
 */

//	"        '  askjdfhjkashdf    $USER'"

int	check_double_simple_dollar_case(char *str)
{
	int	i;
	int	len_str;
	int	condition1;
	int	condition2;

	condition1 = FALSE;
	condition2 = FALSE;
	len_str = (int) ft_strlen(str);

	if (str[0] != D_QUOTE || str[len_str - 1] != D_QUOTE)
		return (FALSE);
	i = 1;

	while (i < len_str - 1)
	{
		if (str[i] == S_QUOTE)
			condition1 = TRUE;

		while (str[i] == ' ' && i < len_str - 1)
			i ++;

		if (str[i] == DOLLAR_SIGN && i + 1 < len_str \
			&& str[i + 1] != ' ' && str[i + 1] != '\0')
			condition2 = TRUE;
//		if (condition1 && condition2 && str[len_str - 2] == S_QUOTE)
		if (condition1 && condition2)
			return (TRUE);
		i ++;
	}
	return (FALSE);
}

/*
		if (str[i] == S_QUOTE)
		{
			i++;
			tmp = str[i];
			while (str[i] == ' ' && i < len_str - 1)
				i ++;
		}
		else
		{
		}
*/

/************ MAIN FUNCTION *************/

/**
 *
 */

void	handle_dollar_cases(t_tokens *token, t_list *env_list)
{
	char	*tmp;
	char	*res;

	tmp = NULL;

	/**
	 * Case: "'$...'"
	 * Description: Expands variables inside double quotes while preserving single quotes.
	 * @example:
	 * Input: "'$USER and test works'"
	 * Output: 'daruuu and test works' (assuming $USER = daruuu).
	 * Steps:
	 * Remove outer double quotes using remove_quotes_str.
	 * Expand variables, skipping content inside single quotes using replace_dollar_variable_skip_s_quote.
	 */
	if (check_double_simple_dollar_case(token->str))
	{
		tmp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(tmp);

		res = replace_dollar_variable_skip_s_quote(token->str, env_list);
		token->str = ft_strdup(res);
		free(tmp);
		return ;
	}

	/**
	 * Case: "$ '...'"
	 * @description: Handles space immediately following $.
	 * @example:
	 * Input: "$ 'some string'"
	 * Output: $ 'some string' (unchanged).
	 * Steps:
	 * Detected by check_dollar_with_space_single.
	 * Managed by handle_dollar_with_space_single.
	 */
	if (check_dollar_with_space_single(token->str))
	{
		handle_dollar_with_space_single(token);
		return ;
	}

	/**
	 * Case: "$'...'"
	 * @description: Processes $ followed directly by single quotes.
	 * @example:
	 * Input: "$'simple string'"
	 * Output: simple string.
	 * Steps:
	 * Remove outer double quotes using remove_quotes_str.
	 * Copy the modified string back to token->str.
	 */
	if (check_doble_dollar_single(token->str))
	{
		tmp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(tmp);
		free(tmp);
		return ;
	}

	/**
	 * Case: "$USER"
	 * Description: Expands a simple environment variable.
	 * @example:
	 * Input: "$USER"
	 * Output: daruuu (assuming $USER = daruuu).
	 * Steps:
	 * Detected by check_dollar_simple.
	 * Managed by handle_single_quotes_after_dollar
	 */
	if (check_dollar_simple(token->str))
	{
		handle_single_quotes_after_dollar(token);
	}
	/**
	 * Case: No expansion required
	 * Description: Handles tokens that should not trigger variable expansion.
	 * @example:
	 * Input: "'string'" or "\"escaped\"".
	 * Output: Remains unchanged.
	 * Steps:
	 * Managed by handle_no_expand_cases
	 */
	if (handle_no_expand_cases(token) == FALSE)
	{
		/**
		 * Default Case: General dollar expansion
		 * Description: Expands variables based on env_list if none of the above cases are matched.
		 * @example:
		 * Input: "$HOME/$USER"
		 * Output: /home/daruu/daruu (assuming $HOME=/home/daruu and $USER=daruu).
		 * Steps:
		 * Managed by expand_dollar.
		 */
		expand_dollar(token, env_list);
		return ;
	}
}
