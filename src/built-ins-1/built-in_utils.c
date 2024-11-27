/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:54:28 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/26 12:46:10 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Buscar una variable por clave en la lista
*/

t_env	*find_env_var(t_list *env_list, char *key)
{
	t_env	*env;

	if (!env_list || !key)
		return (NULL);
	while (env_list != NULL)
	{
		env = (t_env *)env_list->content;
		if (env && env->key && ft_strcmp((char *)env->key, key) == 0)
			return ((t_env *)env);
		env_list = env_list->next;
	}
	return (NULL);
}

void	check_value(char *value, char *line, t_env *env_var)
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

void	create_new_key(char *line, char *key, char *value, t_list **env_list)
{
	t_env	*new_var;
	t_list	*new_node;

	new_var = init_empty_env_node();
	if (!new_var)
	{
		fprintf(stderr, "Error: no se pudo crear la variable\n");
		free(key);
		free(value);
		return;
	}
	new_var->key = key;
	new_var->value = value;
	new_var->full_var = line;

	new_node = ft_lstnew(new_var);
	if (!new_node)
	{
//		printf("Error: no se pudo crear el nodo de la lista\n");
		fprintf(stderr, "Error: no se pudo crear el nodo de la lista\n");
		free_env(new_var);
		return;
	}
//	add node to env_list with ft_lstadd_back
	ft_lstadd_back(env_list, new_node); // Agregar el nodo a la lista
	printf("AFTER LST ADD_BACK\n");
	print_env_list(*env_list);
}

/*
void create_new_key(char *line, char *key, char *value, t_list *env_list)
{
//	t_env *new_var = init_env(line);
	t_env *new_var;


	new_var = init_env(line);
	printf("line: %s\n", line);
	printf("key: %s\n", new_var->key);
	printf("value: %s\n", new_var->key);
	if (!new_var)
	{
		printf("Error: no se pudo crear la variable\n");
		free(key);
		free(value);
		return ;
	}
	ft_lstadd_back((t_list **) env_list, ft_lstnew(new_var));
}
*/


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

//void	export__or_update_var(char *line, t_list **env_list)
void	export_var(char *line, t_list **env_list)
{
	char	*key;
	char	*value;
	t_env	*env_var;

	// Obtener la clave y el valor de la línea
	key = get_var_name(line);
	value = get_var_value(line);

//	Encontrar la variable en el entorno
	env_var = find_env_var(*env_list, key);
	if (env_var == NULL)
	{
		printf("create new key^^^^^^^^^^^^^^^^^^^\n");
		create_new_key(line, key, value, env_list);
	}
	else
	{
		// Si ya existe, actualizar su valor
		check_value(value, line, env_var);
	}
	free(key);
	if (!env_var)
		free(value);
}

/*
void	export_var(char *line, t_list **env_list)
{
	char	*key;
	char	*value;
	t_env	*env_var;
	t_list	*find_node;

	printf("++++++++++=lista env export\n");
	print_env_list(*env_list);

	key = get_var_name(line);
	value = get_var_value(line);
	find_node = *env_list;
	if (find_key_list(find_node, key) == 1)
	{
		env_var = find_env_var(*env_list, key);
		check_value(value, line, env_var);
	}
	else
	{
		// Crear una nueva clave
		create_new_key(line, key, value, env_list);
	}
	free(key); // Liberar memoria reservada para key
}
*/

/*
void	export_var(char *line, t_list **env_list)
{
	char	*key;
	char	*value;
	t_env	*env_var;

	printf("++++++++++=lista env export\n ");
	print_env_list((t_list *) env_list);
	printf("-------------------------\n ");
	key = get_var_name(line);
	value = get_var_value(line);
//
//	printf("key: %s\n", key);
//	printf("value: %s\n", value);
*/
/*	if (!validate_var_name(key))
	{
		printf("Error: nombre de variable no válido\n");
		free(key);
		free(value);
		return;
	}*//*


	env_var = find_env_var((t_list *) env_list, key);
	if (env_var != NULL)
	{
		// Funcion auxiliar para gestionar los casos de value.
		check_value(value, line, env_var);
	}
	else
	{
		// Creacion de nueva Key.
		create_new_key(line, key, value, (t_list *) &env_list);
	}
}
*/
