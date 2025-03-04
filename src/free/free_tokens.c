/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/04 22:54:10 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens_list(t_list **tokens)
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
