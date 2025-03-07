/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:21:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 18:46:23 by dasalaza         ###   ########.fr       */
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
	new_env->next = NULL;
	return (new_env);
}

static int	extract_key_from_var(t_env *new_env, char **split_var)
{
	new_env->key = ft_strdup(split_var[0]);
	if (!new_env->key)
	{
		free_string_matrix(split_var);
		return (FALSE);
	}
	return (TRUE);
}

static int	extract_value_from_var(t_env *new_env, char **split_var)
{
	if (split_var[1] != NULL)
		new_env->value = ft_strdup(split_var[1]);
	else
		new_env->value = ft_strdup("");
	if (!new_env->value)
	{
		free(new_env->key);
		free_string_matrix(split_var);
		return (FALSE);
	}
	return (TRUE);
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
	if (!extract_key_from_var(new_env, split_var) \
		|| !extract_value_from_var(new_env, split_var))
		return (FALSE);
	free_string_matrix(split_var);
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
	if (!split_key_value(new_env, key_value_variable))
	{
		free_env_node(new_env);
		return (NULL);
	}
	return (new_env);
}

/*
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
	if (!new_env->key)
	{
		free_string_matrix(split_var);
		return (FALSE);
	}
	if (split_var[1] != NULL)
	{
		new_env->value = ft_strdup(split_var[1]);
		if (!new_env->value)
		{
			free(new_env->key);
			free_string_matrix(split_var);
			return (FALSE);
		}
	}
	else
	{
		new_env->value = ft_strdup("");
		if (!new_env->value)
		{
			free(new_env->key);
			free_string_matrix(split_var);
			return (FALSE);
		}
	}
	free_string_matrix(split_var);
	return (TRUE);
}
*/
