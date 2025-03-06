/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/06 00:29:05 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens_void(void *content)
{
	t_tokens	*tokens;

	if (!content)
		return ;
	tokens = (t_tokens *)content;
	if (tokens->str)
	{
		free(tokens->str);
		tokens->str = NULL;
	}
	free(tokens);
}
void	free_tokens_list(t_list **tokens)
{
	if (!tokens || !*tokens)
		return;
	ft_lstclear(tokens, free_tokens_void);
	*tokens = NULL;  // ✅ Evita punteros colgantes
}

/*
void	free_tokens_list(t_list **tokens)
{
	t_list		*tmp;
	t_tokens	*token;

	if (!tokens || !*tokens)
		return;
	while (*tokens)
	{
		tmp = (*tokens)->next;
		token = (t_tokens *)(*tokens)->content;
		if (token->str)
			free(token->str);
		free(token);
		free(*tokens);
		*tokens = tmp;
	}
}
*/
