/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:37:04 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/22 17:55:51 by anamedin         ###   ########.fr       */
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
}

void	free_cmd_args(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd_args)
	{
		while (cmd->cmd_args[i])
		{
			free(cmd->cmd_args[i]);
			i++;
		}
		free(cmd->cmd_args);
		cmd->cmd_args = NULL;
	}
}

void	free_cmd_list(t_list *cmd_list)
{
	t_list	*tmp;
	t_cmd	*cmd;
	// int		i;

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
				// i = 0;
				free_cmd_args(cmd);
			}
			if (cmd->cmd_path)
				free(cmd->cmd_path);
			free(cmd);
		}
		free(cmd_list);
		cmd_list = tmp;
	}
}
