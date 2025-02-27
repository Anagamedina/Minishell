/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:21:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/27 17:50:33 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*init_empty_env_node(void)
{
	t_env	*new_env;

	new_env = NULL;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = NULL;
	new_env->value = NULL;
	new_env->full_var = NULL;
	new_env->next = NULL;
	return (new_env);
}

static int	split_key_value(t_env *new_env, char *key_value_variable)
{
	char	**split_var;

	split_var = ft_split(key_value_variable, '=');
	if (!split_var || !split_var[0])
	{
		free_string_matrix(split_var);
		return (FALSE);
	}
	new_env->key = ft_strdup(split_var[0]);
	if (split_var[1] != NULL)
		new_env->value = ft_strdup(split_var[1]);
	else
		new_env->value = ft_strdup("");
	free_string_matrix(split_var);
	if (!new_env->key || !new_env->value)
		return (FALSE);
	return (TRUE);
}

t_env	*create_env_node(char *key_value_variable)
{
	t_env	*new_env;

	if (!key_value_variable)
		return (NULL);
	new_env = init_empty_env_node();
	if (!new_env)
		return (NULL);
	new_env->full_var = ft_strdup(key_value_variable);
	if (!new_env->full_var)
	{
		free(new_env);
		return (NULL);
	}
	if (!split_key_value(new_env, key_value_variable))
	{
		free_env(new_env);
		return (NULL);
	}
	return (new_env);
}
