/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/03/09 13:38:29 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* -------------------------------------------------------------------------- */
/*  init_exec: inicializa estructura de ejecución (env, paths, flags)         */
/* -------------------------------------------------------------------------- */
t_exec	*init_exec(t_list *env_list)
{
	t_exec	*exec_info;

	exec_info = malloc(sizeof(t_exec));
	if (!exec_info)
		return (NULL);
	exec_info->first_cmd = NULL;
	exec_info->env_vars = env_list_to_array(env_list);
	exec_info->pipe_input_fd = -1;
	exec_info->pipe_output_fd = -1;
	exec_info->cmd_count = 0;
	exec_info->paths = get_path(exec_info->env_vars);
	exec_info->is_running = 1;
	if (!exec_info->env_vars)
	{
		free_exec(exec_info);
		return (NULL);
	}
	return (exec_info);
}
