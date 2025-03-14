/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:45:37 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/14 19:20:05 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_redirection(t_cmd *cmd, t_list *current)
{
	t_tokens	*token;

	token = (t_tokens *)current->content;
	if (is_redir(token) && cmd && current->next)
		add_redir_to_cmd(cmd, token, (t_tokens *)current->next->content);
}

t_cmd	*process_command_token(t_tokens *token, char **paths, int *cmd_id)
{
	t_cmd	*new_cmd;

	new_cmd = create_new_command(token, paths);
	if (!new_cmd)
	{
		free_command(new_cmd);
		return (NULL);
	}
	new_cmd->cmd_id = (*cmd_id)++;
	new_cmd->last_cmd = 0;
	return (new_cmd);
}

void	cmds_to_lst(t_list **cmd_lst, t_tokens *tk, char **paths, int *id)
{
	t_cmd	*cmd;
	t_list	*new_node;

	cmd = process_command_token(tk, paths, id);
	if (!cmd)
		return ;
	new_node = ft_lstnew(cmd);
	if (!new_node)
	{
		free_command(cmd);
		return ;
	}
	ft_lstadd_back(cmd_lst, new_node);
}

void	process_command_args(t_list *current, t_cmd *cmd)
{
	count_args(current, cmd);
	add_args(&cmd, current);
}
