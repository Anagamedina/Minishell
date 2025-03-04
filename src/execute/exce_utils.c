/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:14:26 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/04 11:25:37 by anamedin         ###   ########.fr       */
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

char	**allocate_env_array(int env_count)
{
	char	**env_array;

	env_array = ft_calloc(env_count + 1, sizeof(char *));
	if (!env_array)
	{
		handle_memory_allocation_error();
		return (NULL);
	}
	return (env_array);
}

char	**env_list_to_array(t_list *env_list)
{
	t_list	*curr_node;
	char	**env_array;
	int		env_count;
	int		i;

	if (!env_list)
		return (NULL);
	env_count = count_env_variables(env_list);
	env_array = allocate_env_array(env_count);
	if (!env_array)
		return (NULL);
	curr_node = env_list;
	i = 0;
	while (curr_node && i < env_count)
	{
		env_array[i] = ft_strdup(((t_env *)curr_node->content)->full_var);
		if (!env_array[i])
			return (handle_env_duplication_error(env_array, i), NULL);
		curr_node = curr_node->next;
		i++;
	}
	env_array[env_count] = NULL;
	return (env_array);
}
