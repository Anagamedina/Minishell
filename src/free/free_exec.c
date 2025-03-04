/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:18 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/04 22:42:40 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_exec(t_exec *exec)
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
    /*
    if (exec->pipe_input_fd > 0)
        close(exec->pipe_input_fd);
    if (exec->pipe_output_fd > 0)
        close(exec->pipe_output_fd);
    */
    free(exec);
}
