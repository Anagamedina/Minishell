/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:44:53 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 19:54:37 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

/*
void	free_tokens(t_tokens *tokens)
{
	t_tokens	*temp;

	if (!tokens)
		return ;
	while (tokens)
	{
		temp = tokens->next;
		if (tokens->str)
		{
			free(tokens->str);
			// tokens->str = NULL;
		}
		// free(tokens);
		tokens = temp;
	}
}*/
