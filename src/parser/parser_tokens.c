/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:26:52 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 21:19:08 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	update_command_type(t_mini *mini, t_tokens *curr_token)
{
	char	*cmd_path;

	if (is_builtin_command(curr_token->str))
	{
		curr_token->type_token = BUILTINS;
		return (1);
	}
	cmd_path = is_cmd_external(mini, curr_token);
	if (cmd_path)
	{
		curr_token->type_token = CMD_EXTERNAL;
		free(cmd_path);
		return (1);
	}
	print_command_not_found(curr_token->str);
	return (0);
}

void	update_words_in_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_tokens	*curr_token;
	t_tokens	*curr_next_token;

	token_list = mini->tokens;
	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;
		if (curr_token->type_token == WORD && curr_token->is_valid_cmd)
		{
			if (!update_command_type(mini, curr_token))
				return ;
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

static	void	init_parser_vars(t_mini *mini, \
		t_list **token_list, t_list **env_list)
{
	*token_list = mini->tokens;
	*env_list = mini->env;
}

void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;
	t_tokens	*next_token;

	init_parser_vars(mini, &token_list, &env_list);
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
