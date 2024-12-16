/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/16 18:28:12 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char )s2[i]);
}

char	*ft_strncpy(char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

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
	{
		free(out[i]);
	}
	free(out);
}

int	copy_word(t_split_data *data)
{
	data->out[data->k] = (char *)malloc(sizeof(char) * \
		(data->end - data->start + 1));
	if (data->out[data->k] == NULL)
		return (-1);
	ft_strncpy(data->out[data->k], &data->str[data->start], \
	data->end - data->start);
	data->out[data->k][data->end - data->start] = '\0';
	data->k++;
	return (0);
}

