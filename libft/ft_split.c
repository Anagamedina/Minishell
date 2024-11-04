/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:02:07 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/04 17:47:35 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_init_variables(size_t *i, int *count_words, int *index_substr)
{
	*i = 0;
	*count_words = 0;
	*index_substr = -1;
}

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
		while (s[ind] != c && s[ind] != '\0')
			ind++;
	}
	return (num_words);
}

static char	*ft_new_str(const char *s, int start, int end)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *) malloc((end - start + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (start < end)
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

static void	*ft_free_split(char **matrix, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	int		j;
	int		index_substr;
	char	**new_matrix;
	size_t	i;

	ft_init_variables(&i, &j, &index_substr);
	new_matrix = (char **) ft_calloc (ft_wcount(s, c) + 1, sizeof(char *));
	if (!new_matrix)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index_substr < 0)
			index_substr = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index_substr >= 0)
		{
			new_matrix[j] = ft_new_str(s, index_substr, i);
			if (!(new_matrix[j]))
				return (ft_free_split(new_matrix, j));
			index_substr = -1;
			j++;
		}
		i++;
	}
	return (new_matrix);
}
