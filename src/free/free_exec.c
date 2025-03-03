/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:57:18 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/03 14:01:19 by dasalaza         ###   ########.fr       */
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

//
// void	free_exec(t_exec *exec)
// {
// 	if (!exec)
// 		return ;
// 	if (exec->first_cmd)
// 		ft_lstclear(&exec->first_cmd, (void (*)(void *))free_command);  // ✅ Usar `free_command()`
// 	if (exec->env_vars)
// 	{
// 		free_string_matrix(exec->env_vars);
// 		exec->env_vars = NULL;
// 	}
// 	if (exec->paths)
// 	{
// 		free_string_matrix(exec->paths);
// 		exec->paths = NULL;
// 	}
// 	free(exec);
// }