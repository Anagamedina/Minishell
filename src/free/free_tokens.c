/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:44:53 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/27 23:32:01 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	free_tokens(t_tokens *token)
{
	t_tokens	*temp;

	if (!token)
		return ;
	while (token)
	{
		temp = token->next;
		if (token->str)
			free(token->str);
		free(token);
		token = temp;
	}
}
