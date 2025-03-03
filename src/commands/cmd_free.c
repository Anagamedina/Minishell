/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:37:04 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/03 12:32:49 by dasalaza         ###   ########.fr       */
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
		cmd->cmd_args = NULL;
	}
	free(cmd);
}

// void	free_cmd_list(t_list *cmd_list)
// {
// 	t_list	*tmp;
// 	t_cmd	*cmd;
//
// 	while (cmd_list)
// 	{
// 		tmp = cmd_list->next;
// 		if (cmd_list->content)
// 		{
// 			cmd = (t_cmd *)cmd_list->content;
// 			if (cmd)
// 			{
// 				if (cmd->cmd)
// 					free(cmd->cmd);
// 				if (cmd->cmd_args)
// 					free_string_matrix(cmd->cmd_args);
// 				if (cmd->cmd_path)
// 					free(cmd->cmd_path);
// 				free(cmd);
// 			}
// 		}
// 		free(cmd_list);
// 		cmd_list = tmp;
// 	}
// }


void	free_cmd_list(t_list *cmd_list)
{
	t_list	*tmp;
	t_cmd	*cmd;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		if (cmd_list->content)
		{
			cmd = (t_cmd *)cmd_list->content;
			if (cmd)
			{
				if (cmd->cmd)
				{
					free(cmd->cmd);
					cmd->cmd = NULL;
				}
				if (cmd->cmd_args)
				{
					free_string_matrix(cmd->cmd_args);
					cmd->cmd_args = NULL;
				}
				if (cmd->cmd_path)
				{
					free(cmd->cmd_path);
					cmd->cmd_path = NULL;
				}
				free(cmd);
			}
		}
		free(cmd_list);
		cmd_list = tmp;
	}
}
