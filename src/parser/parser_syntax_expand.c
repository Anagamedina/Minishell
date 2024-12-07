//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"

/**
 * check if the next character is a single quote like $'hello
 * echo "'$USER'"
 */
int	check_dollar_after_single_quote(const char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '\'') // Si la siguiente es una comilla simple
				return (1); // Retorna 1 si se detecta
		}
		i++;
	}
	return (0); // Retorna 0 si no encuentra el patrón `$'`
}

/**
 * check if the previous character is a backslash like \\$hello
 * return TRUE or FALSE
 * echo "\$aaa
 */
int	check_backslash_before_dollar(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (i > 0 && str[i - 1] == '\\') // Si la anterior es una comilla doble
				return (1); // Retorna 1 si se detecta
		}
		i++;
	}
	return (0);
}

/**
 * check if the next character is a single quote like $'hello
 * echo "'$USER'"
 *  check backslash before		\\$
 * check single quote after		$'...'
 * llamamos a expand dollar
 */
/************ MAIN FUNCTION *************/

void	handle_variable_expansion(t_tokens *token)
{
	if (check_backslash_before_dollar(token->str) == 1)
	{
		printf("******* backslash before \\$\n");
		printf("token->str: [%s] con id: [%i]\n", token->str, token->id_token);
	}
	else if (check_dollar_after_single_quote(token->str) == 1)
	{
		printf("******* single quote after $\n");
		printf("token->str: [%s] con id: [%i]\n", token->str, token->id_token);
	}
	else
	{
		printf("call function to expand variable\n");
		printf("token->str: [%s] con id: [%i]\n", token->str, token->id_token);
	}
}
