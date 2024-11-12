/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:30 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/12 13:30:33 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *ft_strncpy(char *s1, char *s2, int n)
{
	int i = 0;
	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

static int	count_words(char *str)
{
	int i = 0;
	int wc = 0;
	int in_quotes = 0;
	char quote;

	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			in_quotes = 1;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] == quote)
				in_quotes = 0;
			i++; // Saltar la comilla de cierre
			wc++;
		}
		else if (str[i] && !in_quotes)
		{
			wc++;
			while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
				i++;
		}
	}
	return (wc);
}

char **ft_split_quote(char *str)
{
	int i = 0,
	start = 0,
	end = 0,
	k = 0;
	int wc = count_words(str);
	char **out = (char **)malloc(sizeof(char *) * (wc + 1));

	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		start = i;
		if (str[i] == '\'' || str[i] == '"')
		{
			char quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			i++; // Saltar la comilla de cierre
		}
		else
		{
			while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
				i++;
		}
		end = i;
		if (end > start)
		{
			out[k] = (char *)malloc(sizeof(char) * (end - start + 1));
			ft_strncpy(out[k++], &str[start], end - start);
		}
	}
	out[k] = NULL;
	return (out);
}
