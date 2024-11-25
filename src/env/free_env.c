/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:05:01 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/23 11:05:04 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
 * using this function to free the env list local variable
 */

void	free_env(t_env *env)
{
	if (!env)
		return;

	// Liberar los campos dinámicos si fueron asignados
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	if (env->full_var)
		free(env->full_var);
	// Liberar la estructura en sí
	free(env);
}
