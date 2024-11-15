/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:34:31 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/07 13:35:45 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*init_struct_env(void)
{
	t_env	*new_envp;

	new_envp = (t_env *)malloc(sizeof(t_env));
	if (!new_envp)
		return (NULL);
	new_envp->value = NULL;
	new_envp->key = NULL;
	new_envp->full_var = NULL;
	new_envp->next = NULL;
	return (new_envp);
}

/*
 * Crea un nodo de una lista enlazada para almacenar una variable local.
 * Obtiene el nombre (key) y el valor (value) de la variable a partir de una línea en formato NOMBRE=VALOR.
 * Retorna un puntero a la estructura creada, o NULL si ocurre un error.
 */
t_env	*create_local_vars_list(char *line)
{
	t_env	*local_variable;

	local_variable = init_struct_env();
	if (local_variable == NULL)
		return (NULL);
	local_variable->key = get_var_name(line);
	local_variable->value = get_var_value(line);
	local_variable->next = NULL;
	return (local_variable);
}
