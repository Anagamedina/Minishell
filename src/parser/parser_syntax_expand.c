/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:26:47 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/03 11:08:29 by  dasalaza        ###   ########.fr       */
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
	if (check_d_quote_dollar_s_quote(token->str)) //$'..'
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

//	"        '$USER '"

int	check_double_simple_dollar_case(char *str)
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

//	printf("len - 1: [%c]\n", str[len_str - 1]);

	while (i < len_str - 1)
	{
		tmp = str[i];
//		printf("curr i: [%d] char:[%c]\n", i, tmp);

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
	 * this 3 cases are valid:
	 * " ' $USER ' "
	 * ""' $USER ' ""
	 * " " " ' $USER ' " " "
	 * 
	 * Steps: 
	 * Expands variables inside d_quotes while preserving single quotes.
	 * Remove outer double quotes using remove_quotes_str.
	 * Expand variables, skip data inside single quotes
	 */
	// TODO: rename function
	if (check_double_simple_dollar_case(token->str))
	{
		printf("original str: [%s]\n", token->str);

		tmp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(tmp);
		printf("after remove_quotes_str: [%s]\n", token->str);

		res = replace_dollar_variable_skip_s_quote(token->str, env_list);
		token->str = ft_strdup(res);
		printf("after replace_dollar_variable : [%s]\n", token->str);

		free(tmp);

		return ;
	}

	/**
	 * Case: "$'...'"
	 * Case: " $ '...'"
	 * Case: " $ $ '...'"
	 * Error case: " $$ '...'"
	 * 
	 * Steps:
	 * the dollar between d_quote and s_quote
	 * only one d_quote (open and close) 
	 * can have spaces between d_quote and s_quote
	 * can't have 2 consecutives dollar signs ($$) 
	 */

	// TODO: rename function
	if (check_dollar_with_space_single(token->str))
	{
		handle_dollar_with_space_single(token);
		return ;
	}

	/**
	 * Case: "$'...'"
	 * Steps:
	 * Remove outer double quotes using remove_quotes_str.
	 * Copy the modified string back to token->str.
	 */
	/*
	if (check_d_quote_dollar_s_quote(token->str))
	{
		tmp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(tmp);
		free(tmp);
		return ;
	}
	*/

	/**
	 * Case: "$'USER"
	 * Case: "this is the paht: $PATH"
	 * 
	 * Steps:
	 * Expands a simple environment variable.
	 * Detected by check_dollar_simple.
	 * Managed by handle_single_quotes_after_dollar
	 */
	/*
	if (check_dollar_simple(token->str))
	{
		handle_single_quotes_after_dollar(token);
	}
	*/

	/**
	 * Case: No expansion required
	 * @details: Handles tokens that should not trigger variable expansion.
	 * @example: "'string'" or "\"escaped\"".
	 * Output: Remains unchanged.
	 * Steps:
	 * Managed by handle_no_expand_cases
	 */
	if (handle_no_expand_cases(token) == FALSE)
	{
		/**
		 * Case: General dollar expansion
		 * Expands variables based on env_list if none of the above cases are matched.
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
