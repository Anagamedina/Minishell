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

/**
 * validar el nombre de la variable
 * validar el valor de la variable
 * ana=bonita
 */

int	validate_local_var_syntax(char *new_local_var)
{
	if (!(validate_var_name(new_local_var)))
	{
		printf("Error validating var_name\n");
		return (FALSE);
	}
	if (!(validate_var_value(new_local_var)))
	{
		printf("Error validating var_value\n");
		return (FALSE);
	}
	return (TRUE);
}

/*
 * Crea un nodo de una lista enlazada para almacenar una variable local
 * en el entorno actual del shell.
 * get name (key) and value (value) de la variable
 * formato
 * NOMBRE=VALOR.
 * Retorna un puntero a la estructura creada, o NULL si ocurre un error.
 */

t_list	*create_local_vars_list(char *line, t_list *local_vars_list)
{
	t_env	*local_vars;
	t_list	*new_node;

	if (!(validate_local_var_syntax(line)))
	{
		printf("Error: invalid local variable syntax: %s\n", line);
		return (local_vars_list); // Devuelve la lista sin cambios
	}
	local_vars = init_env(line);
	if (!local_vars)
	{
		printf("Error: failed to initialize local variable: %s\n", line);
		return (local_vars_list); // Devuelve la lista sin cambios
	}
	new_node = ft_lstnew(local_vars);
	if (!new_node)
	{
		free_env(local_vars);
		printf("Error: failed to create list node for: %s\n", line);
		return (local_vars_list);
	}
	ft_lstadd_back(&local_vars_list, new_node);
	return (local_vars_list);
}
