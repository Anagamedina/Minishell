/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:18 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/06 17:41:42 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	free_exec(t_exec *exec)
{
	if (!exec)
		return;

	// Asegurar que no haya referencias activas
	exec->is_running = 0;

	if (exec->env_vars)
	{
		free_string_matrix(exec->env_vars);
		exec->env_vars = NULL;
	}

	if (exec->paths)
	{
		free_string_matrix(exec->paths);
		exec->paths = NULL;
	}

	if (exec->first_cmd)
	{
		free_cmd_list(&exec->first_cmd);
	}
	if (exec)
		free(exec);
}






// void	free_exec(t_exec *exec)
// {
// 	if (!exec)
// 		return;
//
// 	if (exec->env_vars)
// 	{
// 		if (!exec->is_running)
// 			free_string_matrix(exec->env_vars);
// 		exec->env_vars = NULL;
// 	}
//
// 	if (exec->paths)
// 	{
// 		if (!exec->is_running)
// 			free_string_matrix(exec->paths);
// 		exec->paths = NULL;
// 	}
//
// 	// if (exec->first_cmd)
// 	// 	ft_lstclear(&exec->first_cmd, (void (*)(void *))free_command);
// 	if (exec->first_cmd)
// 	{
// 		free_cmd_list(&exec->first_cmd);
// 	}
//
// 	free(exec);
// }
