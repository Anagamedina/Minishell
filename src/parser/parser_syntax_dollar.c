//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"

/**
 * Processes a token and handles quotes, special cases, and variable expansion.
 *
 * Depending on the token type:
 * @see handle_single_quote Removes quotes from tokens with single quotes.
 * @see remove_quotes_str Strips quotes from the token string.
 *
 * @param token Pointer to the token being processed.
 * @param env_list Pointer to the linked list of environment variables.
 */
void	handle_tokens(t_tokens *token, t_list *env_list)
{
	char	*tmp;

	if (handle_single_quote(token))	// echo '$hello' ->printf($hello)
	{
		tmp = remove_quotes_str(token->str, S_QUOTE);
		token->str = ft_strdup(tmp);
		return ;
	}
	if (handle_special_quotes(token))	//  echo "'$USER'" -> 'catalinaburgos'
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
			handle_dollar_cases(token, env_list);
		return ;
	}
	if (handle_double_quotes(token))	// echo "$USER"
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
			handle_dollar_cases(token, env_list);	//expand variables
		return ;
	}
	if (ft_strchr_true(token->str, DOLLAR_SIGN))
	{
//		$USER
		handle_dollar_cases(token, env_list);	//expand variables
		return ;
	}
}
//	$echo "'$USER'"
//	$echo "'$USER88huh'"

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

	if ((curr_token->type_token == BUILTINS) && (token_list->next != NULL) \
	&& (((t_tokens *) (token_list->next->content))->type_token == WORD))
	{
		// Iterate through the curr_token list starting from the second node
		while (token_list->next != NULL)
		{
			curr_token = (t_tokens *)token_list->next->content;
			if (curr_token->type_token == WORD)
				handle_tokens((t_tokens *) curr_token, env_list);
			else
				break ;
			token_list = token_list->next;
		}
	}
}
