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

t_env	*init_env(char *line)
{
	t_env *new_env;
	char **key_var;

	new_env = malloc(sizeof(t_env));
	if(!new_env)
		return (NULL);
	new_env->full_var = ft_strdup(line);
	key_var = ft_split(line, '=');
	new_env->key = key_var[0];
	new_env->value = key_var[1];
	new_env->next = NULL;
}


t_list	*init_env_list(char **envp)
{
	t_list *env_list;
	t_list *new_env;
	t_env *new_node;
	int i;


	i = 0;
	while (envp[i] != NULL)
	{
		new_env = (t_list *)init_env(envp[i]);
		new_node = ft_lstnew(new_env);
		if (!new_node) {
			free(new_env);
			ft_lstclear(&env_list, free);
			return (NULL);
		}
		ft_lstadd_back(&env_list, (t_list *)new_node);
		i++;
	}
	return (env_list);
}



/*void print_env_list(t_list *env_list)
{
	t_list *current = env_list;
	t_env *env;

	while (current != NULL)
	{
		env = (t_env *)current->content;
		printf("%s=%s\n", env->key, env->value);
		current = current->next;
	}
}*/