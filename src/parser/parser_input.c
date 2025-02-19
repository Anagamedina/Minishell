/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:58 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/19 16:23:57 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_file(t_tokens *curr_token, t_tokens *curr_next)
{
	int	fd;

	if (!curr_token && !curr_next)
		return ;
	if (curr_token->str && curr_next->str)
	{
		if (is_redir(curr_token) == TRUE)
		{
			if (curr_next->type_token == FILENAME)
			{
				fd = open_file(curr_next->str, REDIR_OUT);
				if (fd == -1)
				{
					perror("Error abriendo archivo de SALIDA");
				}
			}
		}
	}
}

void	parse_redir(t_mini *mini)
{
	t_list		*token_list;
	t_tokens	*curr_token;
	t_tokens	*curr_token_next;

	token_list = mini->tokens;
	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;
		if (token_list->next == NULL)
			return ;
		curr_token_next = (t_tokens *)token_list->next->content;
		if (!curr_token_next || !curr_token_next->str)
			return ;
		if (is_redir(curr_token) == TRUE)
		{
			if (curr_token_next->type_token != FILENAME)
				return ;
			check_file(curr_token, curr_token_next);
		}
		token_list = token_list->next;
	}
}
