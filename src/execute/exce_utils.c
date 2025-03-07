/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:14:26 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 16:42:23 by anamedin         ###   ########.fr       */
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

char	**env_list_to_array(t_list *env_list)
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
	{
		perror("Error: can't assign memory to env_list_to_array");
		return (NULL);
	}
	curr_node = env_list;
	i = 0;
	while (curr_node && i < env_count)
	{
		curr_env_var = (t_env *)curr_node->content;
		if (!curr_env_var || !curr_env_var->key)
		{
			free_env_array(env_array, i);
			perror("Error: Invalid environment variable");
			return (NULL);
		}
		temp_str = ft_strjoin(curr_env_var->key, "=");
		if (!temp_str)
		{
			free_env_array(env_array, i);
			perror("Error: Can't allocate memory for env variable");
			return (NULL);
		}
		env_array[i] = ft_strjoin(temp_str, curr_env_var->value);
		free(temp_str);
		if (!env_array[i])
		{
			free_env_array(env_array, i);
			perror("Error: Can't create env variable string");
			return (NULL);
		}
		curr_node = curr_node->next;
		i++;
	}
	env_array[env_count] = NULL;
	return (env_array);
}
