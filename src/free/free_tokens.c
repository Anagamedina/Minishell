/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/08 14:43:26 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens_void(void *content)
{
	t_tokens	*tokens;

	if (!content)
		return ;
	tokens = (t_tokens *)content;
	if (!tokens)
	{
		return ;
	}
	
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
	{
		return ;
	}
	ft_lstclear(tokens, free_tokens_void);
	*tokens = NULL;
}

