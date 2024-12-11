//
// Created by daruuu on 12/7/24.
//
#include "../../includes/minishell.h"

int handle_double_quotes(t_tokens *token)
{
	if (token->str[0] == '\"' && token->str[token->length - 1] == '\"')
	{
			return (TRUE);
	}
	return (FALSE);
}

int handle_single_quote(t_tokens *token)
{
	if (token->str[0] == '\'' && token->str[token->length - 1] == '\'')
	{
		return (TRUE);
	}
	return (FALSE);
}

/**
 * check if the string start with double quote and end with double quote
 * check if the string start with single quote and end with single quote
 * @example echo "'$'USER''"	printf() -> '$'USER''
 * check_single_quote_after_dollar(token->str)
 * " ' ' "
 */
int	handle_special_quotes(t_tokens *token)
{
	if (token->str[0] == '\"' && token->str[token->length - 1] == '\"' \
		&& token->str[1] == '\'' &&
		token->str[token->length - 2] == '\'') // echo " '$USER' "
	{
		return (TRUE);
	}
	return (FALSE);
}
