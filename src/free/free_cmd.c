/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:18 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/27 22:48:07 by dasalaza         ###   ########.fr       */
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