/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/04 01:01:59 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_list **tokens)
{
	t_list		*temp;
	t_tokens	*token;

	if (!tokens || !*tokens)
		return;
	while (*tokens)
	{
		token = (t_tokens *)(*tokens)->content;
		if (token)
		{
			if (token->str)
				free(token->str);
			free(token);
		}
		temp = (*tokens)->next;
		free(*tokens);
		*tokens = temp;
	}
	*tokens = NULL;
}


/*void	free_tokens(t_list **tokens)
{
	t_list	*temp;

    if (!tokens || !*tokens)
        return;

	while (*tokens)
	{
		free((*tokens)->content);
		temp = (*tokens)->next;
		free(*tokens);
		*tokens = temp;
	}
	*tokens = NULL;
}*/

/*
void	free_tokens(t_list *tokens_list)
{
	t_list		*temp;
	t_tokens	*token;

	if (!tokens_list)
		return ;
	while (tokens_list)
	{
		temp = tokens_list->next;
		token = (t_tokens *)tokens_list->content;
		if (token)
		{
			if (token->str)
				free(token->str);
			free(token);
		}
		free(tokens_list);
		tokens_list = temp;
	}
}
*/
