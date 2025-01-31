/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:47:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/31 14:11:44 by dasalaza         ###   ########.fr       */
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
			free_string_array(cmd->cmd_args);
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		// if (cmd->redir_list)
//			free_redir(cmd->redir_list);
		free(cmd);
		cmd = temp;
	}
}

t_cmd	*handle_cmd_error(t_cmd *new)
{
	perror("Error: Command not found here!!");
	if (new->cmd_args)
		free_string_array(new->cmd_args);
	// free(new);
	return (NULL);
}
