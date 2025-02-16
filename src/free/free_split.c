/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:54:27 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 19:53:50 by dasalaza         ###   ########.fr       */
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
		i ++;
	}
	free(matrix_2d);
}

void	free_split_data(t_split_data *split_data)
{
	if (!split_data)
		return ;
	if (split_data->out)
	{
		free_string_matrix(split_data->out);
	}
	if (split_data->str)
		free(split_data->str);
	free(split_data);
}

/*
void	free_split_result(char **out)
{
	int	i;

	i = 0;
	while (out[i] != NULL)
	{
		free(out[i]);
		i ++;
	}
	free(out);
}
*/

void	free_split_result_struct(char **out, int k)
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
