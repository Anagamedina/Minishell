/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:48:37 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/18 10:44:30 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
void	free_command(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	if (cmd->cmd_args)
	{
		while (cmd->cmd_args[i] != NULL)
		{
			free(cmd->cmd_args[i]);
			i ++;
		}
		free(cmd->cmd_args);
	}
	// free(cmd);
}

void	free_cmd_list(t_list *cmd_list)
{
	t_list *tmp;
	t_cmd *cmd;
	int i;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		cmd = (t_cmd *)cmd_list->content;
		if (cmd)
		{
			if (cmd->cmd)
				free(cmd->cmd);

			if (cmd->cmd_args)
			{
				i = 0;
				while (cmd->cmd_args[i] != NULL)
				{
					free(cmd->cmd_args[i]);
					i++;
				}
				free(cmd->cmd_args);
			}
			if (cmd->cmd_path)
				free(cmd->cmd_path);
			

			// Si tienes otras estructuras o listas dentro de cmd, libéralas aquí
			// Por ejemplo, redir_list si existe
			//if (cmd->redir_list) {
				//free(cmd->redir_list);  // Esto dependerá de cómo hayas gestionado la memoria en t_redir
			//}

			free(cmd);  
		}
		free(cmd_list); 
		cmd_list = tmp; 
	}
}