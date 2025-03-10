/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:50:56 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/10 11:10:19 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_redir_after_pipe(t_list *token_list)
{
	t_tokens	*curr_token;
	t_tokens	*next_token;

	while (token_list)
	{
		curr_token = (t_tokens *)token_list->content;
		if (curr_token->type_token == PIPE && token_list->next)
		{
			next_token = (t_tokens *)token_list->next->content;
			if (is_redir(next_token))
			{
				return (FALSE);
			}
		}
		token_list = token_list->next;
	}
	return (TRUE);
}

int	validate_pipes_and_separators(t_list *token_list)
{
	if (!check_start_and_end_tokens(token_list) || \
			!check_consecutive_operators(token_list))
		return (FALSE);
	return (TRUE);
}

/*int	validate_syntax(t_list *token_list)
{
	if (!check_redir_after_pipe(token_list))
		return (FALSE);
	if (!check_repeated_redirections(token_list) || \
		!validate_pipes_and_separators(token_list))
		return (FALSE);
	return (TRUE);
}*/


int	validate_syntax(t_list *token_list, t_mini *mini)
{
	if (!check_redir_after_pipe(token_list))
	{
		mini->exit_status = 2; 
		return (FALSE);
	}
	if (!check_repeated_redirections(token_list) || \
		!validate_pipes_and_separators(token_list))
	{
		mini->exit_status = 2;  
		return (FALSE);
	}
	return (TRUE);
}

