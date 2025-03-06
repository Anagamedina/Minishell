/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:46:15 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/06 10:43:34 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	free_redir(t_redir *redir)
// {
// 	t_redir	*temp;
//
// 	while (redir)
// 	{
// 		temp = redir->next;
// 		if (redir->filename)
// 			free(redir->filename);
// 		free(redir);
// 		redir = temp;
// 	}
// }


void	free_redir(void *content)
{
	t_redir *redir = (t_redir *)content;

	if (!redir)
		return;
	if (redir->filename)
		free(redir->filename);
	free(redir);
}


void free_redir_list(t_list **redir_list)
{
	if (!redir_list || !*redir_list)
		return;
	ft_lstclear(redir_list, free_redir);
	*redir_list = NULL;
}