/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:02:07 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/08 20:08:46 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(const char *s, char c)
{
	int	num_words;
	int	ind;

	num_words = 0;
	ind = 0;
	while (s[ind] != '\0')
	{
		while (s[ind] == c && s[ind] != '\0')
			ind++;
		if (s[ind] != c && s[ind] != '\0')
			num_words++;
		while (s[ind] != '\0' && s[ind] != c)
			ind++;
	}
	return (num_words);
}

static char	*ft_new_str(const char *s, int start, int end)
{
	int		i;
	char	*str;

	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

static void	ft_free_split(char **matrix, int count)
{
	int	i;

	i = 0;
	if (!*matrix)
		return ;
	while (i < count)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

static int	ft_add_word(char **matrix, const char *s, int *index, int *j)
{
	matrix[*j] = ft_new_str(s, index[0], index[1]);
	if (!matrix[*j])
	{
		ft_free_split(matrix, *j);
		return (0);
	}
	index[0] = -1;
	(*j)++;
	return (1);
}

char	**ft_split(const char *s, char c)
{
	int		index_substr[2];
	char	**new_matrix;
	size_t	i;
	int		j;

	ft_init_variables(&i, &j, &index_substr[0]);
	new_matrix = (char **) ft_calloc (ft_wcount(s, c) + 1, sizeof(char *));
	if (!new_matrix)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index_substr[0] < 0)
			index_substr[0] = (int) i;
		else if ((s[i] == c || i == ft_strlen(s)) && index_substr[0] >= 0)
		{
			index_substr[1] = (int) i;
			if (!ft_add_word(new_matrix, s, index_substr, &j))
			{
				return (NULL);
			}
		}
		i++;
	}
	return (new_matrix);
}
