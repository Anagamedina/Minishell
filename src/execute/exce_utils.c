/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:14:26 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 18:39:42 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_env_variables(t_list *env_list)
{
	t_list	*curr_node;
	int		env_count;

	curr_node = env_list;
	env_count = 0;
	while (curr_node)
	{
		env_count ++;
		curr_node = curr_node->next;
	}
	return (env_count);
}

void	free_env_array(char **env_array, int allocated)
{
	while (allocated > 0)
	{
		free(env_array[allocated]);
		allocated--;
	}
	free(env_array);
}

char	*convert_env_variable_to_string(t_env *env_var)
{
	char	*temp_str;
	char	*env_string;

	if (!env_var || !env_var->key)
		return (NULL);
	temp_str = ft_strjoin(env_var->key, "=");
	if (!temp_str)
		return (NULL);
	env_string = ft_strjoin(temp_str, env_var->value);
	free(temp_str);
	return (env_string);
}

int	populate_env_array(t_list *env_list, char **env_array, int env_count)
{
	t_list	*curr_node;
	t_env	*curr_env_var;
	int		i;

	curr_node = env_list;
	i = 0;
	while (curr_node && i < env_count)
	{
		curr_env_var = (t_env *)curr_node->content;
		env_array[i] = convert_env_variable_to_string(curr_env_var);
		if (!env_array[i])
		{
			free_env_array(env_array, i);
			return (0);
		}
		curr_node = curr_node->next;
		i++;
	}
	env_array[env_count] = NULL;
	return (1);
}

char	**env_list_to_array(t_list *env_list)
{
	char	**env_array;
	int		env_count;

	if (!env_list)
		return (NULL);
	env_count = count_env_variables(env_list);
	env_array = ft_calloc(env_count + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	if (!populate_env_array(env_list, env_array, env_count))
	{
		free(env_array);
		return (NULL);
	}
	return (env_array);
}

/*char	**env_list_to_array(t_list *env_list)
{
	t_list	*curr_node;
	t_env	*curr_env_var;
	char	**env_array;
	int		env_count;
	int		i;
	char	*temp_str;

	if (!env_list)
		return (NULL);
	env_count = count_env_variables(env_list);
	env_array = ft_calloc(env_count + 1, sizeof(char *));
	if (!env_array)
		return (NULL);
	curr_node = env_list;
	i = 0;
	while (curr_node && i < env_count)
	{
		curr_env_var = (t_env *)curr_node->content;
		if (!curr_env_var || !curr_env_var->key)
		{
			free_env_array(env_array, i);
			return (NULL);
		}
		temp_str = ft_strjoin(curr_env_var->key, "=");
		if (!temp_str)
		{
			free_env_array(env_array, i);
			return (NULL);
		}
		env_array[i] = ft_strjoin(temp_str, curr_env_var->value);
		free(temp_str);
		if (!env_array[i])
		{
			free_env_array(env_array, i);
			return (NULL);
		}
		curr_node = curr_node->next;
		i++;
	}
	env_array[env_count] = NULL;
	return (env_array);
}*/
