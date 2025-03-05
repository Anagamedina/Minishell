/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:54:27 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/04 23:02:20 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_string_matrix(char **matrix_2d)
{
	int	i;

	if (!matrix_2d)
		return ;
	i = 0;
	while (matrix_2d[i])
	{
		free(matrix_2d[i]);
		i++;
	}
	free(matrix_2d);
}

void	free_partial_split(char **out, const int k)
{
	int	i;

	i = 0;
	if (!out)
		return ;
	while (i < k)
	{
		free(out[i]);
		i ++;
	}
}
