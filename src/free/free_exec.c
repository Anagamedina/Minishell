/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:18 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/05 23:00:34 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_exec(t_exec *exec)
{
	if (!exec)
		return;

	if (exec->env_vars)
	{
		if (!exec->is_running)
			free_string_matrix(exec->env_vars);
		exec->env_vars = NULL;
	}

	if (exec->paths)
	{
		if (!exec->is_running)
			free_string_matrix(exec->paths);
		exec->paths = NULL;
	}

	if (exec->first_cmd)
		ft_lstclear(&exec->first_cmd, (void (*)(void *))free_command);

	free(exec);
}


/*void	free_exec(t_exec *exec)
{
	if (!exec)
		return;
	if (exec->first_cmd)
		ft_lstclear(&exec->first_cmd, (void (*)(void *))free_command);
	if (exec->env_vars)
	{
		free_string_matrix(exec->env_vars);
		// exec->env_vars = NULL;  // ✅ Evita doble liberación
	}
	if (exec->paths)
	{
		free_string_matrix(exec->paths);
		// exec->paths = NULL;  // ✅ Evita doble liberación
	}
	// if (exec->pipe_input_fd >= 0)  // ✅ Evita cerrar fds inválidos
	// 	close(exec->pipe_input_fd);
	// if (exec->pipe_output_fd >= 0)
	// 	close(exec->pipe_output_fd);

	free(exec);
	exec = NULL;  // ✅ Evita accesos indebidos a memoria liberada
}*/

/*void	free_exec(t_exec *exec)
{
    if (!exec)
        return;
    if (exec->first_cmd)
		ft_lstclear(&exec->first_cmd, (void (*)(void *))free_command);
    if (exec->env_vars)
    {
    	free_string_matrix(exec->env_vars);
    }
    if (exec->paths)
    {
		free_string_matrix(exec->paths);
    }
    if (exec->pipe_input_fd > 0)
        close(exec->pipe_input_fd);
    if (exec->pipe_output_fd > 0)
        close(exec->pipe_output_fd);

    free(exec);
}*/