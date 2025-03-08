/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:39:52 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/08 14:43:14 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*init_command(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->cmd_args = NULL;
	new_cmd->count_args = -1;
	new_cmd->cmd_path = NULL;
	new_cmd->cmd_id = 0;
	new_cmd->is_builtin = -1;
	new_cmd->is_external = -1;
	new_cmd->input_fd = -1;
	new_cmd->output_fd = -1;
	new_cmd->has_pipe = -1;
	new_cmd->last_cmd = -1;
	new_cmd->redir_list = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	handle_command_not_found(t_cmd *cmd, t_tokens *current_token)
{
	write(2, "bash: ", 6);
	write(2, current_token->str, ft_strlen(current_token->str));
	write(2, ": command not found\n", 20);
	if (!cmd)
        return ;

}

t_cmd	*create_new_command(t_tokens *current_token, char **paths)
{
	t_cmd	*new_cmd;

	if (!current_token || !current_token->str)
		return (NULL);
	new_cmd = init_command();
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = current_token->str;
	if (!new_cmd->cmd)
		return (free_command(new_cmd), NULL);
	if (current_token->type_token == BUILTINS)
		new_cmd->is_builtin = 1;
	else if (current_token->type_token == CMD_EXTERNAL)
	{
		new_cmd->is_external = 1;
		new_cmd->cmd_path = get_cmd_path(current_token, paths);
		if (!new_cmd->cmd_path)
		{
			handle_command_not_found(new_cmd, current_token);
			return (NULL);
		}
	}
	return (new_cmd);
}
