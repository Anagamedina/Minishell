/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:05:01 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/23 11:05:04 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"
/*
 * using this function to free the env list local variable
 */
void	free_env_list(t_env *head)
{
	t_env *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp->full_var);

		free(tmp);
	}
}
