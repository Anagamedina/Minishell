/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:27:00 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 15:52:48 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i] != '\0')
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
	}
	return (wc);
}

static char	**allocate_output_array(int wc)
{
	return ((char **)malloc(sizeof(char *) * (wc + 1)));
}

static void	free_output_array(char **out, int words_allocated)
{
	int	i;

	i = 0;
	while (i < words_allocated)
		free(out[i++]);
	free(out);
}

static int	copy_word(char *str, char **out, int j, int *k)
{
	int	i;

	i = j;
	while (str[i] && (str[i] != ' ') && (str[i] != '\0'))
		i++;
	out[*k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
	if (!out[*k])
	{
		free_output_array(out, *k);
		return (-1);
	}
	ft_strncpy(out[*k], &str[j], i - j);
	out[*k][i - j] = '\0';
	(*k)++;
	return (0);
}

static void	fill_output_array(char *str, char **out)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		j = i;
		while (str[i] && (str[i] == ' '))
			i++;
		while (str[i] != '\0' && str[i] != ' ')
			i++;
		while (str[i] && (str[i] == ' ') && str[i] != '\0')
			i++;
		if (i > j)
		{
			k = copy_word(str, out, j, &k);
			if (k == -1)
				return ;
		}
	}
	out[k] = NULL;
}

char	**ft_split_new_version(char *str)
{
	int		wc;
	char	**out;

	wc = count_words(str);
	out = allocate_output_array(wc);
	if (!out)
		return (NULL);
	fill_output_array(str, out);
	return (out);
}
