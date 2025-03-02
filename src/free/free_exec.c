/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:18 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/27 22:40:53 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:47:17 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 19:56:08 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->first_cmd)
	{
		ft_lstclear(&exec->first_cmd, free);
		exec->first_cmd = NULL;
	}
	if (exec->env_vars)
		free_string_matrix(exec->env_vars);
	if (exec->paths)
		free_string_matrix(exec->paths);
	if (exec->pipe_input_fd > 0)
		close(exec->pipe_input_fd);
	if (exec->pipe_output_fd > 0)
		close(exec->pipe_output_fd);
	free(exec);
}


/*int count_env_variables_ia(char **env_vars)
{
	int count = 0;

	if (!env_vars)
		return (0);
	while (env_vars[count])
		count++;
	return (count);
}


void free_exec(t_exec *exec_info)
{
	if (!exec_info)
		return;
	if (exec_info->env_vars)
		free_env_array(exec_info->env_vars, count_env_variables_ia(exec_info->env_vars));
	if (exec_info->paths)
	{
		int i = 0;
		while (exec_info->paths[i])
			free(exec_info->paths[i++]);
		free(exec_info->paths);
	}
	free(exec_info);
}*/