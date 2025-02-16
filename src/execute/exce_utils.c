/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:48:37 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/26 00:45:41 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

char	**lst_to_arr(t_list *env_list)
{
	t_list	*node;
	t_env	*current;
	char	**arr;
	int		count = 0;

	node = env_list;
	while (node)
	{
		count++;
		node = node->next;
	}

	arr = ft_calloc(count + 1, sizeof(char *)); // +1 para NULL final
	if (!arr)
		return NULL;
	node = env_list;
	count = 0;
	while (node)
	{
		current = (t_env *)node->content;
		arr[count] = ft_strdup(current->full_var);
		if (!arr[count])
		{
			while (count > 0)
				free(arr[--count]);
			free(arr);
			return NULL;
		}
		count++;
		node = node->next;
	}
	arr[count] = NULL; // Terminar el array con NULL
	return arr;
}
