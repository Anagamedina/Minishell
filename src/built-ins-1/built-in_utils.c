/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:54:28 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/25 11:10:05 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Buscar una variable por clave en la lista
t_env	*find_env_var (t_list *env_list, char *key)
{
	t_list	*current;
	t_env	*env;

	current = env_list;
	while (current != NULL)
	{
		env = (t_env *)current->content;
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		current = current->next;
	}
	return (NULL);
}



/*
 * Función que agrega un nuevo nodo al final de la lista de variables de entorno.
 */
/*void	add_env_back(t_env **env_list, t_env *new_node)
{
	t_env	*current;

	if(!env_list || !new_node)
		return ;

	current = *env_list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}*/


void 	check_value(char *value, char *line, t_env *env_var)
{
	if (value && ft_strcmp(line, "+="))
		env_var->value = ft_strjoin(env_var->value, value);
	else if (value && ft_strcmp(line, "="))
	{
		free(env_var->value);
		env_var->value = value;
	}
	else if(!value)
		env_var->value = ft_strdup("");

}

void create_new_key(char *line, char *key, char *value, t_list **env_list)
{
	t_env *new_var = init_env(line);
	if (!new_var)
	{
		printf("Error: no se pudo crear la variable\n");
		free(key);
		free(value);
		return ;
	}
	ft_lstadd_back(env_list, ft_lstnew(new_var));
}


int	only_export(t_env *env_list)
{
	while (env_list != NULL)
	{
		printf("declare -x %s=\"%s\"\n", env_list->key, env_list->value);
		env_list= env_list->next;
	}
	return (0);
}


//**********MAIN FUNCTION********** */
void	export_var(char *line, t_list **env_list)
{
	char	*key;
	char	*value;
	t_env	*env_var;

	key = get_var_name(line);
	value = get_var_value(line);

	if (!validate_var_name(key))
	{
		printf("Error: nombre de variable no válido\n");
		free(key);
		free(value);
		return;
	}

	env_var = find_env_var(*env_list, key);
	if (env_var)
	{
		// Funcion auxiliar para gestionar los casos de value.
		check_value(value, line, env_var);
	}
	else
	{
		// Creacion de nueva Key.
		create_new_key(line, key, value, env_list);
	}
}


