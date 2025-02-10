/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:54:28 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/10 23:12:49 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_list*	create_new_key(char* line, char* key, char* value)
{
	t_env	*new_var;
	t_list	*new_node;

	new_var = init_empty_env_node();
	if (!new_var)
	{
		fprintf(stderr, "Error: cant create new variable\n");
		free(key);
		free(value);
		return (NULL);
	}
	new_var->key = key;
	new_var->value = value;
	new_var->full_var = line;
	new_node = ft_lstnew(new_var);
	if (!new_node)
	{
		fprintf(stderr, "Error: no se pudo crear el nodo de la lista\n");
		free_env(new_var);
		return (NULL);
	}
	// Creemos que no hay que freir new_var porque new_node apunta a new_var.
	// free_env(new_var);
	return (new_node);
}


void	print_export(t_list **env_list)
{
	t_list	*tmp;
	t_env	*env_var;

	if (!env_list || !*env_list)
		return ;
	tmp = *env_list;
	while (tmp != NULL)
	{
		env_var = (t_env *)(tmp->content);
		if (env_var)	//&& env_var->key)
		{
			if (env_var->value)
				printf("declare -x %s=\"%s\"\n", env_var->key, env_var->value);
			else
				printf("declare -x %s=\"\"\n", env_var->key);
		}
		tmp = tmp->next;
	}
}

//**********MAIN FUNCTION********** */

void	update_var(char *line, t_list **env_list)
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
		printf("create new key\n");
		create_new_key(line, key, value);
	}
	else
		check_value(value, line, env_var);
	free(key);
	if (!env_var)
		free(value);
}