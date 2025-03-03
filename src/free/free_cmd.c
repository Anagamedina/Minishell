/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:18 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/03 12:17:40 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	temp = NULL;
	while (cmd)
	{
		temp = cmd->next;
		if (cmd->cmd)
			free(cmd->cmd);
		if (cmd->cmd_args)
			free_string_matrix(cmd->cmd_args);
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		if (cmd->redir_list)
		{
			ft_lstclear(&cmd->redir_list, free);
			cmd->redir_list = NULL;
		}
		free(cmd);
		cmd = temp;
	}
}

t_cmd	*handle_cmd_error(t_cmd *new)
{
	perror("Error: Command not found here!!");
	if (new->cmd_args)
		free_string_matrix(new->cmd_args);
	return (NULL);
}


/*void free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd_args)
	{
		int i = 0;
		while (cmd->cmd_args[i])
			free(cmd->cmd_args[i++]);
		free(cmd->cmd_args);
	}
	if (cmd->redir_list) // ✅ Liberar la lista de redirecciones antes de liberar cmd
		free_redirections(cmd->redir_list);
	free(cmd);
}*/


/*void free_redirections(t_list *redir_list)
{
	t_list *tmp;
	t_redir *redir;

	while (redir_list)
	{
		tmp = redir_list->next;
		redir = (t_redir *)redir_list->content;
		free(redir);
		free(redir_list);
		redir_list = tmp;
	}
}*/


