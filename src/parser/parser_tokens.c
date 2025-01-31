/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:38:46 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/30 12:04:55 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

//se pude poner en una funcion esta parte:
//porque veo que se repite varias veces.

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


 static void	handle_special_cases(t_tokens *token, t_list *env_list, t_tokens *next_token)
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
		 return;
	 }
	 if (handle_special_quotes(token))
	 {
		 handle_special_cases(token, env_list, next_token);
		 return;
	 }
	 if (has_even_double_quotes(token))
	 {
		 handle_dollar_cases(token, env_list, next_token);
		 return;
	 }
	 if (ft_strchr_true(token->str, DOLLAR_SIGN))
		 handle_dollar_cases(token, env_list, next_token);
	else 
		return;
 }



void	update_words_in_tokens(t_mini *mini)
{
	t_list *token_list;
	t_tokens *curr_token;

	token_list = mini->tokens;
	while (token_list != NULL)
	{
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
		token_list = token_list->next;
	}
}


void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;
	t_tokens	*next_token;

	update_words_in_tokens(mini);

	token_list = mini->tokens;
	env_list = mini->env;

	if (token_list && (((t_tokens *) token_list->content)->type_token == BUILTINS || \
		((t_tokens *) token_list->content)->type_token == CMD_EXTERNAL))
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
		if (curr_token->type_token == PIPE || curr_token->type_token == DELIMITER || \
						curr_token->type_token == CMD_EXTERNAL || curr_token->type_token == BUILTINS)
		{	
			token_list = token_list->next;
			continue;
		}
		else
			break;
	}
}