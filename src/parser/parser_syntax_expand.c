/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:26:47 by catalinab         #+#    #+#             */
/*   Updated: 2024/12/17 19:06:56 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_dollar_simple(char *str);

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
static int  handle_single_quotes_after_dollar(t_tokens *token)
{
	char *temp;

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

static int handle_one_digit_after_dollar(t_tokens *token)
{
	//free(token->str);
	token->str = ft_strdup("");
	return (TRUE);
}

static int	handle_string_before_dollar(t_tokens *token)
{
	char *temp;

	temp = remove_quotes_str(token->str, D_QUOTE);
	//free(token->str); sale un doble free
	token->str = ft_strdup(temp);
	if (!token->str)
	{
		perror("error: ft_strdup failed");
		return (FALSE);
	}
	free (temp);
	temp = ft_substr(token->str, 0, ft_strchr(token->str, DOLLAR_SIGN) - token->str);
	free(token->str);
	token->str = ft_strdup(temp);
	free(temp);
	return (TRUE);
}

static int handle_digit_and_more_after_dollar(t_tokens *token)
{
	char *temp;


	if (token->str[0] == D_QUOTE && token->str[token->length - 1] == D_QUOTE)
	{
		temp = remove_quotes_str(token->str, D_QUOTE);
		//free(token->str);
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
static int	check_dollar_special_quote(const char *str)
{
	if (ft_strchr_true(str, DOLLAR_SIGN) \
		&& ft_strchr_true(str, D_QUOTE) && ft_strchr_true(str, S_QUOTE))
		return (TRUE);
	return (FALSE);
}

static int	handle_no_expand_cases(t_tokens *token)
{
	printf("token actual: %s\n", token->str);
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

static int handle_dollar_with_space_single(t_tokens *token)
{
	char	*temp;

	temp = remove_quotes_str(token->str, D_QUOTE);
//	free(token->str);
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

/************ MAIN FUNCTION *************/

void	handle_dollar_cases(t_tokens *token, t_list *env_list)
{
	char	*tmp;

	tmp = NULL;

	// Caso "$ '...'" -> espacio después del dólar
	if (check_dollar_with_space_single(token->str))
	{
		handle_dollar_with_space_single(token);
		return ;
	}
	// "$'...'" ----> imprime
	if (check_doble_dollar_single(token->str))
	{
		tmp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(tmp);
		free(tmp);
		return ;
	}

	if (check_dollar_simple(token->str)) // Maneja $'...'
	{
		handle_single_quotes_after_dollar(token);
	}
	free(tmp);
	if (!handle_no_expand_cases(token))
		expand_dollar(token, env_list);
}
