/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:44:53 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/31 13:52:01 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

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
			tokens->str = NULL;
		}
		// free(tokens);
		tokens = temp;
	}
}
