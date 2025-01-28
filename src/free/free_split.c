/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:54:27 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/27 23:00:38 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	free_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i ++;
	}
	free(array);
}

void	free_split_data(t_split_data *split_data)
{
	if (!split_data)
		return;
	if (split_data->out)
	{
		free_string_array(split_data->out);
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
