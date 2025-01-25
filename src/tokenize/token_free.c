/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/24 15:13:40 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split_result(char **out)
{
	int	i;

	i = 0;
	while (out[i] != NULL)
	{
		free(out[i]);
		i++;
	}
	free(out);
}

void	free_split_result_struct(char **out, int k)
{
	int	i;

	i = 0;
	while (out[k] != NULL && i < k)
		free(out[i]);
	free(out);
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i ++;
	}
}

void	free_mini_list(t_mini *minishell)
{
	if (!minishell)
		return ;
	if (minishell->exec)
		free(minishell->exec);
	if (minishell->token)
		free(minishell->token);
	free(minishell);
}
