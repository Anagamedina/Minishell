/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 12:36:20 by anamedin         ###   ########.fr       */
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
		if (env && env->key && ft_strcmp(env->key, key) == 0)
			return (env);
		env_list = env_list->next;
	}
	return (NULL);
}

static t_env	*create_env_variable(char *key, char *value)
{
	t_env	*new_var;

	if (!key)
		return (NULL);
	new_var = init_empty_env_node();
	if (!new_var)
		return (NULL);
	new_var->key = key;
	if (!new_var->key)
		return (free_env_node(new_var), NULL);
	if (value)
	{
		new_var->value = value;
		if (!new_var->value)
			return (free_env_node(new_var), NULL);
	}
	return (new_var);
}

t_list	*create_new_env_node(char *key, char *value)
{
	t_env	*new_var;
	t_list	*new_node;

	new_var = create_env_variable(key, value);
	if (!new_var)
		return (NULL);
	new_node = ft_lstnew(new_var);
	if (!new_node)
	{
		free_env_node(new_var);
		return (NULL);
	}
	return (new_node);
}

void	print_export(t_list **env_list)
{
	t_list	*tmp;
	t_env	*env_var;

	if (!env_list || !*env_list)
		return ;
	tmp = *env_list;
	while (tmp)
	{
		env_var = (t_env *)(tmp->content);
		if (env_var && env_var->key)
		{
			printf("declare -x %s", env_var->key);
			if (env_var->value != NULL)
			{
				printf("=\"%s\"", env_var->value);
			}
			printf("\n");
		}
		tmp = tmp->next;
	}
}