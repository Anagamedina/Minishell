/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:01:34 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/07 14:19:05 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: falta corregir este codigo

t_env	*init_env_list(char **envp)
{
	t_env	*head = NULL;
	t_env	*new_env;
	t_env	*current = NULL;
	int 	i;
	char 	**key_var;

	i = 0;
	while (envp[i] != NULL)
	{
		new_env = init_struct_env();
		if (!new_env)
			return (NULL);
		new_env->full_var = ft_strdup(envp[i]);
		key_var = ft_split(envp[i], '=');
		new_env->key = key_var[0];
		new_env->value = key_var[1];
		if (head == NULL)
			head = new_env; // Establecer la cabeza de la lista
		else
			current->next = new_env;
		current = new_env;
		free(key_var);
		i++;
	}
	return (head);
}

void	print_env_list(t_env *env_list)
{
	while (env_list != NULL)
	{
		printf("%s\n", env_list->full_var);
		env_list = env_list->next;
	}
}
// env
t_env	*get_env(char **envp)
{
	t_env	*new_env;

	new_env = NULL;
	new_env = init_env_list(envp);
	if (!new_env)
		return (NULL);
	return(new_env);
}




/*
 * find key iterating througth list
 * and change env->value;
 */
/*
void	modify_var_env(t_env **list_envp, char *key)
{
    
}
*/
/*
 *	crear una nueva VARIABLE de entorno a nuestro ENV
 *	call init_struct_env()
 *	ft_lst_add_back()
 */
/*
t_env	*add_new_var(t_env **list_envp, char *new_var)
{
}
*/
