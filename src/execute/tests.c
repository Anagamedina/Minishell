/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:02:00 by catalinab         #+#    #+#             */
/*   Updated: 2025/03/02 19:17:06 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"



static int	count_env_variables(t_list *env_list)
{
	t_list	*curr_node;
	int		env_count;

	curr_node = env_list;
	env_count = 0;
	while (curr_node)
	{
		env_count ++;
		curr_node = curr_node->next;
	}
	return (env_count);
}

void	free_exec(t_exec *exec_info)
{
	if (!exec_info)
		return;
	if (exec_info->env_vars)
		free_env_array(exec_info->env_vars, count_env_variables(exec_info->env_vars));
	if (exec_info->paths)
	{
		int i = 0;
		while (exec_info->paths[i])
			free(exec_info->paths[i++]);
		free(exec_info->paths);
	}
	free(exec_info);
}


/*void	free_cmd(t_cmd *cmd)
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
	if (cmd->redir_list)
		free(cmd->redir_list);  // Si es una lista dinámica, recorrer y liberar nodos.
	free(cmd);
}*/


void free_cmd(t_cmd *cmd)
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
	free(cmd);
}