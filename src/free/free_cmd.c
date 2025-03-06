/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:18 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/06 11:31:47 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command_void(void *content)
{
	t_cmd	*cmd;

	if (!content)
		return ;
	cmd = (t_cmd *)content;

	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->cmd_args)
		free_string_matrix(cmd->cmd_args);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->redir_list)
		// ft_lstclear(&cmd->redir_list, free_redir);
			free_redir_list(&cmd->redir_list);
	free(cmd);
}

void	free_cmd_list(t_list **cmd_list)
{
	if (!*cmd_list)
		return ;
	ft_lstclear(cmd_list, (void (*) (void *))free_command_void);
	*cmd_list = NULL;
}

void	free_command(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->cmd_args)
		free_string_matrix(cmd->cmd_args);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->redir_list)
	{
		// ft_lstclear(&cmd->redir_list, free);
		free_redir_list(&cmd->redir_list);
		// cmd->redir_list = NULL;
	}
	free(cmd);
}

t_cmd	*handle_cmd_error(t_cmd *new)
{
	perror("Error: Command not found here!!");
	if (new->cmd_args)
		free_string_matrix(new->cmd_args);
	return (NULL);
}