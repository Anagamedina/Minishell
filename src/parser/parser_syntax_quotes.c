//
// Created by daruuu on 12/7/24.
//
#include "../../includes/minishell.h"

//"' '"
/**
 * check if the string start with double quote and end with double quote
 * check if the string start with single quote and end with single quote
 * @example echo "'$'USER''"	printf() -> '$'USER''
 * check_single_quote_after_dollar(token->str)
 * " ' ' "
 */
void	handle_special_quotes(t_tokens *token)
{
	if (token->str[0] == '\"' &&
		token->str[token->length - 1] == '\"' &&
		token->str[1] == '\'' &&
		token->str[token->length - 2] == '\'') // echo " '$USER' "
	{
		if (check_dollar_after_single_quote(token->str) == 1)
		{
//			skip doble quotes and printf()
			printf("single quote after $,  NO expand\n");
			printf("token->str: [%s]\n", token->str);
		}
		else if (check_backslash_before_dollar(token->str) == 1)
		{
			printf("******* backslash before \\$\n");
			printf("token->str: [%s] con id: [%i]\n", token->str, token->id_token);
		}
		else if (ft_strchr_true(token->str, 36) == 1)
		{
			printf("call function to expand variable in handle_special_quote()\n");
		}
	}
}

void	handle_special_doble_quotes(t_tokens *token)
{
	if (token->str[0] == '\"' && token->str[token->length - 1] == '\"')
	{
		if (check_dollar_after_single_quote(token->str) == 1)
		{
//			skip doble quotes and printf()
			printf("single quote after $,  NO expand\n");
			printf("token->str: [%s]\n", token->str);
		}
		else if (check_backslash_before_dollar(token->str) == 1)
		{
			printf("******* backslash before \\$\n");
			printf("token->str: [%s] con id: [%i]\n", token->str, token->id_token);
		}
		else if (ft_strchr_true(token->str, 36) == 1)
		{
			printf("call function to expand variable in handle_special_quote()\n");
		}
	}
}


void handle_single_quote(t_tokens *token)
{
	if (token->str[0] == '\'' && token->str[token->length - 1] == '\'')
	{
		printf("print token->str without simple quotes\n");
	}
}
