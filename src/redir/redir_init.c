/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:55:30 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/19 16:02:25 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redir	*init_redirection(t_tokens *token, t_tokens *next_token)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	if (next_token && next_token->type_token == FILENAME)
		new_redir->filename = ft_strdup(next_token->str);
	else
		new_redir->filename = NULL;
	if (!new_redir->filename)
	{
		perror("Error: al duplicar el nombre del archivo");
		free(new_redir);
		return (NULL);
	}
	new_redir->type = token->type_token;
	new_redir->fd_input = -1;
	new_redir->fd_output = -1;
	new_redir->next = NULL;
	return (new_redir);
}

void	add_redir_to_cmd(t_cmd *cmd, t_tokens *redir_tk,
						t_tokens *file_tk)
{
	t_redir	*new_redir;
	t_list	*new_node;

	if (!cmd || !redir_tk || !file_tk)
		return ;
	new_redir = init_redirection(redir_tk, file_tk);
	if (!new_redir)
		return ;
	new_node = ft_lstnew(new_redir);
	if (!new_node)
	{
		free(new_redir->filename);
		free(new_redir);
		return ;
	}
	if (!cmd->redir_list)
		cmd->redir_list = new_node;
	else
		ft_lstadd_back(&cmd->redir_list, new_node);
}
