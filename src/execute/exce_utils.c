/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:14:26 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/19 16:14:31 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env_variables(t_list *env_list)
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

	env_count = count_env_variables(env_list);
	env_array = ft_calloc(env_count + 1, sizeof(char *));
	if (!env_array)
	{
		perror("Error: cant assign memory to env_list_to_array");
		return (NULL);
	}
	curr_node = env_list;
	i = 0;
	while (i < env_count)
	{
		curr_env_var = (t_env *)curr_node->content;
		env_array[i] = ft_strdup(curr_env_var->full_var);
		if (!env_array[i])
		{
			perror("Error: No se pudo duplicar variable de entorno");
			free_env_array(env_array, i);
			return (NULL);
		}
		curr_node = curr_node->next;
		i ++;
	}
	env_array[env_count] = NULL;
	return (env_array);
}
