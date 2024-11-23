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


void	create_local_var(char *line, t_list **local_vars)
{
	t_env *new_local_var;

	if (!(validate_var_name(line)))
	{
		printf("Error validating var_name\n");
		return ;
	}
	if (!(validate_var_value(line)))
	{
		printf("Error validating var_value\n");
		return ;
	}
	new_local_var = init_env(line);
	ft_lstadd_back(local_vars, ft_lstnew(new_local_var));
}


/*
 * Crea un nodo de una lista enlazada para almacenar una variable local
 * en el entorno actual del shell.
 * get name (key) and value (value) de la variable
 * formato NOMBRE=VALOR.
 * Retorna un puntero a la estructura creada, o NULL si ocurre un error.
 */
t_env	*create_local_vars_list(char *line)
{
	t_env	*local_vars;

	local_vars = init_env_list();
	if (local_vars == NULL)
		return (NULL);
	local_vars->key = get_var_name(line);
	local_vars->value = get_var_value(line);
	local_vars->next = NULL;
	return (local_vars);
}
