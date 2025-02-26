/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:26:52 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/26 17:52:34 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_and_replace_quotes(t_tokens *token, char quote_type)
{
	char	*tmp;

	tmp = remove_quotes_str(token->str, quote_type);
	if (tmp)
	{
		free(token->str);
		token->str = ft_strdup(tmp);
		free(tmp);
	}
}

static	void	handle_special_cases(t_tokens *token, t_list *env_list, \
		t_tokens *next_token)
{
	if (ft_strchr_true(token->str, DOLLAR_SIGN))
		handle_dollar_cases(token, env_list, next_token);
	else
		remove_and_replace_quotes(token, D_QUOTE);
}

void	handle_tokens(t_tokens *token, t_list *env_list, t_tokens *next_token)
{
	if (handle_single_quote(token))
	{
		remove_and_replace_quotes(token, S_QUOTE);
		return ;
	}
	if (handle_special_quotes(token))
	{
		handle_special_cases(token, env_list, next_token);
		return ;
	}
	if (has_even_double_quotes(token) \
			|| ft_strchr_true(token->str, DOLLAR_SIGN))
		handle_dollar_cases(token, env_list, next_token);
	if (has_even_double_quotes(token))
		handle_dollar_cases(token, env_list, next_token);
	if (ft_strchr_true(token->str, DOLLAR_SIGN))
		handle_dollar_cases(token, env_list, next_token);
}

/*
	TODO: check comands syntax to fix error with more than one type->token the same type
	echo hello echo
	while no encuentres un delimitador el 1ro es un BUILTIN or EXTERNAL y despues del limitador
	un BUILTIN O EXTERNAL
*/
void	update_words_in_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_tokens	*curr_token;
	t_tokens	*curr_next_token;

	token_list = mini->tokens;
	while (token_list != NULL)
	{
		//echo echo | echo hi
		//echo echo;  echo hi
		// echo -> builtin
		// echo -> builtin
		//despues de la pipe sea un word
		curr_token = (t_tokens *)token_list->content;
		if (curr_token->type_token == WORD)
		{
			if (is_builtin_command(curr_token->str))
				curr_token->type_token = BUILTINS;
			else if (is_cmd_external(mini, curr_token))
				curr_token->type_token = CMD_EXTERNAL;
			else
				curr_token->type_token = WORD;
		}
		else if (is_redir(curr_token) && token_list->next != NULL)
		{
			curr_next_token = (t_tokens *)token_list->next->content;
			if (curr_next_token->type_token == WORD)
				curr_next_token->type_token = FILENAME;
		}
		token_list = token_list->next;
	}
}

void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;
	t_tokens	*next_token;

	token_list = mini->tokens;
	env_list = mini->env;
	if ((token_list && \
				is_builtin_or_external ((t_tokens *) token_list->content)))
		token_list = token_list->next;
	while (token_list != NULL)
	{
		curr_token = (t_tokens *) token_list->content;
		if (token_list->next != NULL)
			next_token = (t_tokens *) token_list->next->content;
		else
			next_token = NULL;
		if (curr_token->type_token == WORD)
			handle_tokens(curr_token, env_list, next_token);
		if (is_special_token(curr_token))
		{
			token_list = token_list->next;
			continue ;
		}
		token_list = token_list->next;
	}
}
