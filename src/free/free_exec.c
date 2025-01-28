/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:47:17 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/27 23:19:36 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_exec(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->first_cmd)
		free_cmd((t_cmd *)exec->first_cmd);
	if (exec->env_vars)
		free_string_array(exec->env_vars);
	if (exec->paths)
   		free_string_array(exec->paths);
	free(exec);
}
