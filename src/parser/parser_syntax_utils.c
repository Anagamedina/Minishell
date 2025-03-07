/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 20:06:19 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 20:06:31 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	update_token_validity(t_tokens *token, t_tokens *prev_token, \
		int *command_found)
{
	if (token->type_token == WORD)
	{
		if (!(*command_found) || !prev_token || \
				prev_token->type_token == PIPE || \
				prev_token->type_token == DELIMITER)
		{
			token->is_valid_cmd = TRUE;
			*command_found = TRUE;
		}
		else
			token->is_valid_cmd = FALSE;
	}
	else if (token->type_token == PIPE || token->type_token == DELIMITER)
		*command_found = FALSE;
}

int	validate_and_update_words_positions(t_mini *mini)
{
	t_list		*current;
	t_tokens	*prev_token;
	t_tokens	*token;
	int			command_found;

	if (!mini->tokens)
		return (FALSE);
	current = mini->tokens;
	prev_token = NULL;
	command_found = FALSE;
	while (current)
	{
		token = (t_tokens *)current->content;
		update_token_validity(token, prev_token, &command_found);
		prev_token = token;
		current = current->next;
	}
	return (TRUE);
}

int	check_consecutive_operators(t_list *token_list)
{
	t_list		*current;
	t_tokens	*token;
	t_tokens	*prev;

	current = token_list;
	prev = NULL;
	while (current)
	{
		token = (t_tokens *)current->content;
		if (prev && (prev->type_token == PIPE || \
					prev->type_token == DELIMITER) && \
				(token->type_token == PIPE || token->type_token == DELIMITER))
		{
			print_syntax_error_token(token->str);
			return (FALSE);
		}
		if (prev && is_redir(prev) && token->type_token == PIPE)
		{
			print_syntax_error_token("|");
			return (FALSE);
		}
		prev = token;
		current = current->next;
	}
	return (TRUE);
}
