/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:33:15 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/19 16:33:55 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*init_env_var(char *key_value_var)
{
	t_env	*new_env;
	char	**split_var;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->full_var = ft_strdup(key_value_var);
	if (!new_env->full_var)
	{
		free(new_env);
		return (NULL);
	}
	split_var = ft_split(key_value_var, '=');
	new_env->key = ft_strdup(split_var[0]);
	if (split_var[1] != NULL)
		new_env->value = ft_strdup(split_var[1]);
	else
		new_env->value = ft_strdup("");
	free_string_matrix(split_var);
	if (!new_env->key || !new_env->value)
	{
		free_env(new_env);
		return (NULL);
	}
	new_env->next = NULL;
	return (new_env);
}

t_env	*init_empty_env_node(void)
{
	t_env	*new_env;

	new_env = NULL;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
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
	t_list	*new_node;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		new_env = init_env_var(envp[i]);
		if (!new_env)
		{
			ft_lstclear(&env_list, (void (*)(void *))free_env);
			return (NULL);
		}
		new_node = ft_lstnew(new_env);
		if (!new_node)
		{
			free_env(new_env);
			ft_lstclear(&env_list, (void (*)(void *))free_env);
			return (NULL);
		}
		ft_lstadd_back(&env_list, new_node);
		i ++;
	}
	return (env_list);
}

void print_env_list(t_list *env_list)
{
	t_list *current = env_list;
	t_env *env_var;

	while (current)
	{
		env_var = (t_env *)current->content;
		if (!env_var || !env_var->key)
		{
			write(2, "Warning: Variable de entorno inválida\n", 38);
			current = current->next;
			continue;
		}

		if (env_var->value)
			printf("%s=%s\n", env_var->key, env_var->value);
		else
			printf("%s\n", env_var->key);
		current = current->next;
	}
}
