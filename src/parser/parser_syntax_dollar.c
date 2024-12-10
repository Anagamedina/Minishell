//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"



char	*remove_quotes_str(char *str, char c)
{
	int		i;
	int		j;
	int		new_len;
	char	*new_str;

	i = 0;
	new_len = 0;
	// Calcula la longitud del nuevo string sin el carácter c
	while (str[i] != '\0')
	{
		if (str[i] != c)
			new_len++;
		i++;
	}
	new_str = (char *)malloc(sizeof(char) * (new_len + 1));
	if (new_str == NULL)
		return (NULL);
	// Reconstruye el nuevo string sin el carácter c
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(str); // Libera el string original
	return (new_str);
}

/**
 * Parses the token list and expands variables for tokens of type WORD.
 *
 * This function checks if the first token is of type BUILTINS, followed by
 * a token of type WORD.
 * iterates through the token list and
 * expands any variables (tokens containing `$`)
 * using the environment variable list.
 *
 * @param mini Pointer to the main minishell structure,
 * which contains the token list and environment variables.
 */

void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;

	token_list = mini->token;
	env_list = mini->env;
	curr_token = (t_tokens *) token_list->content; //rellanmos curr_token

/*
	int	is_builtin = curr_token->type_token == BUILTINS;
	int	has_next_token = token_list->next != NULL;
	int condicion3 = ((t_tokens *) (token_list->next->content))->type_token == WORD;

	if (is_builtin && has_next_token && condicion3)
*/
	if ((curr_token->type_token == BUILTINS) && (token_list->next != NULL) \
	&& (((t_tokens *) (token_list->next->content))->type_token == WORD))
	{
		// Iterate through the curr_token list starting from the second node
		while (token_list->next != NULL)	//lista de token_list
		{
			curr_token = (t_tokens *)token_list->next->content;//
			if (curr_token->type_token == WORD)
				handle_tokens((t_tokens *) curr_token, env_list);
			else
				break ;
			token_list = token_list->next; // move to the next node in the list
		}
	}
}

/**
 * Processes a token and handles quotes, special cases, and variable expansion.
 *
 * This function checks the type of quoting or syntax present in the token.
 * Depending on the token type, it removes quotes, expands variables, or
 * handles special cases like `$` inside double quotes or unquoted strings.
 *
 * @param token Pointer to the token being processed.
 * @param env_list Pointer to the linked list of environment variables.
 */
void	handle_tokens(t_tokens *token, t_list *env_list)
{
	char	*result;
	t_env	*first_env;

	// Handle single quotes:
	if (handle_single_quote(token))	// echo '$hello' ->printf($hello)
	{
		printf("processing single-quoted token\n");
		result = remove_quotes_str(token->str, SINGLE_QUOTE);
		printf("%s\n", result);
		expand_dollar(token, first_env);
		return ;
	}
	if (handle_special_quotes(token) == 1)	// echo " '$USER' "
	{
		if (ft_strchr_true(token->str, 36) == 1)
			handle_dollar_cases(token, env_list);
		return ;
	}
	if (handle_double_quotes(token) == 1)	// echo "$USER"
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN) == 1)
			handle_dollar_cases(token, env_list);	//expand variables
		return ;
	}
	if (ft_strchr_true(token->str, DOLLAR_SIGN))
		handle_dollar_cases(token, env_list);	//expand variables
}
