/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:59:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/14 15:20:26 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:01:34 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/12 11:51:49 by dasalaza         ###   ########.fr       */
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
		// new_env->value = "";
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
			// fprintf(stderr, "Error: Can't init env variable: [%s]\n", envp[i]);
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

void	print_env_list(t_list *env_list)
{
	t_list	*current;
    t_env	*env_var;

    current = env_list;
    while (current)
    {
        env_var = (t_env *) current->content;
        if (env_var->key && env_var->value)
		{
        	printf("%s=%s\n", env_var->key, env_var->value);
		}
        current = current->next;
    }
}