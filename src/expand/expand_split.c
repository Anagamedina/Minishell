/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:27:00 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 11:32:49 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words(const char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i] != '\0')
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i ++;
		if (str[i])
			wc ++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i ++;
	}
	return (wc);
}

static void	free_output_array(char **out)
{
	int	i;

	i = 0;
	if (!out)
		return ;
	while (out[i] != NULL)
	{
		free(out[i]);
		i ++;
	}
	free(out);
}

static int	copy_word_in_split(char *str, char **out, int j, int *k)
{
	int	i;

	i = j;
	while (str[i] && (str[i] != ' '))
		i ++;
	out[*k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
	if (!out[*k])
		return (-1);
	ft_strncpy(out[*k], &str[j], i - j);
	out[*k][i - j] = '\0';
	(*k)++;
	return (0);
}

static int	fill_output_array(char *str, char **out)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		j = i;
		while (str[i] && (str[i] == ' '))
			i ++;
		if (str[i] != '\0')
		{
			if (copy_word_in_split(str, out, j, &k) == -1)
			{
				free_output_array(out);
				return (-1);
			}
			while (str[i] && str[i] != ' ')
				i ++;
		}
	}
	out[k] = NULL;
	return (0);
}

char	**ft_split_new_version(char *str)
{
	int		wc;
	char	**out;

	out = NULL;
	wc = count_words(str);
	if (wc == 0)
		return (NULL);
	out = malloc(sizeof(char *) * (wc + 1));
	if (!out)
		return (NULL);
	if (fill_output_array(str, out) == -1)
		return (NULL);
	return (out);
}

