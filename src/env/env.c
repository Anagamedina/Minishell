/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:01:34 by anamedin          #+#    #+#             */
/*   Updated: 2025/01/24 00:32:44 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*init_env(char *line)
{
	t_env	*new_env;
	char	**split_var;

	new_env = NULL;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->full_var = ft_strdup(line);
	if (!new_env->full_var)
	{
		free(new_env);
		return (NULL);
	}
	split_var = ft_split(line, '=');
	if (!split_var)
	{
		free(new_env->full_var);
		free(new_env);
		return (NULL);
	}
	new_env->key = split_var[0];
    new_env->value = split_var[1];
	new_env->next = NULL;
	free(split_var);
	return (new_env);
}

t_env	*init_empty_env_node(void)
{
	t_env *new_env = NULL;

	new_env = malloc(sizeof(t_env));
	if(!new_env)
		return (NULL);
	new_env->full_var = NULL;
	new_env->key = NULL;
	new_env->value = NULL;
	new_env->next = NULL;
	return (new_env);
}

t_list	*init_env_list(char **envp)
{
    t_list	*env_list;
    t_env	*new_env;
    int		i;

    env_list = NULL;
    i = 0;
    while (envp[i] != NULL)
    {
        new_env = init_env(envp[i]);
        if (!new_env)
        {
			free_env(new_env);
            // ft_lstclear(&env_list, free_env);
            // ft_lstclear(&env_list, free);
            return (NULL);
        }
        ft_lstadd_back(&env_list, ft_lstnew(new_env)); // Añade el nuevo nodo
        i ++;
    }
    return (env_list);
}

void	print_env_list(t_list *env_list)
{
	t_list *current;
	t_env  *env;

	if (!env_list)
	{
		printf("La lista de variables de entorno está vacía o no fue inicializada.\n");
		return ;
	}
	current = env_list;
	while (current != NULL)
	{
		if (current->content)
		{
			env = (t_env *)current->content;
			if (env->key)
				printf("%s=", env->key);
			else
				printf("(null)=");

			if (env->value)
				printf("%s\n", env->value);
			else
				printf("(null)\n");
		}
		current = current->next;
	}
}

