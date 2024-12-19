/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:30 by anamedin          #+#    #+#             */
/*   Updated: 2024/12/16 18:20:23 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Skips characters within quotes (single or double) in a string.
 * - Starts at position `*i`, advancing until the matching closing
 * quote is found.
 * - Updates `*i` to the position after the closing quote.
 * - Returns TRUE if a matching quote is found, otherwise FALSE.
 */
/*
static int	skip_quotes(const char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
	{
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

*/
/**
 * Counts the number of "words" in a string,
 * considering spaces, tabs, newlines, quotes (single or double),
 * and special characters (';', '|').
 * - Handles quoted substrings as single words.
 * - Returns the total count of words.
 */
/*
static int	count_words(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i] == BACKSLASH || str[i] == D_QUOTE)
			wc += skip_quotes(str, &i);
		else if (str[i] == ';' || str[i] == '|')
		{
			wc++;
			i++;
		}
		else if (str[i])
		{
			wc++;
			while ((str[i] && (str[i] != ' ' && str[i] != '\t') \
			&& (str[i] != '\n' && str[i] != ';' && str[i] != '|')))
				i++;
		}
	}
	return (wc);
}
*/

/*
 * Advances the index `*i` in the string `str` past any whitespace characters
 * (spaces, tabs, and newlines).
 * - Updates `*i` to the position of the first non-whitespace character.
 */
/*
static void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
		(*i)++;
}

static int	copy_word(char **out, char *str, int start, int end, int *k)
{
	out[*k] = (char *)malloc(sizeof(char) * (end - start + 1));
	if (out[*k] == NULL)
		return (-1);
	ft_strncpy(out[(*k)++], &str[start], end - start);
	return (0);
}

static int	init_vars_split(int *i, int *k, int *wc, char ***out, char *str)
{
	*i = 0;
	*k = 0;
	*wc = count_words(str);
	*out = (char **)malloc(sizeof(char *) * (*wc + 1));
	if (!*out)
		return (-1);
	return (0);
}

*/

/*
char	**ft_split_quote(char *str)
{
	int		i;
	int		j;
	int		k;
	int		wc;
	char	**out;

	if (init_vars_split(&i, &k, &wc, &out, str) == -1)
		return (NULL);
	while (str[i] != '\0' && k < wc)
	{
		skip_whitespace(str, &i);
		j = i;
		if (str[i] == BACKSLASH || str[i] == D_QUOTE)
			skip_quotes(str, &i);
		if (str[i] == SEMICOLON || str[i] == PIPE)
			i++;
		else
		{
			while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' \
				&& str[i] != ';' && str[i] != '|'))
				i++;
		}
		if (i > j && copy_word(out, str, j, i, &k) == -1)
			return (NULL);
	}
	out[k] = NULL;
	return (out);
}
*/

static int	skip_quotes(const char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
	{
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

static void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
		(*i)++;
}

static int	count_words(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		skip_whitespace(str, &i);
		if (str[i] == BACKSLASH || str[i] == D_QUOTE)
			wc += skip_quotes(str, &i);
		else if (str[i] == SEMICOLON || str[i] == PIPE)
		{
			wc++;
			i++;
		}
		else if (str[i])
		{
			wc++;
			while (str[i] && str[i] != ' ' && str[i] != '\t' \
			&& str[i] != '\n' && str[i] != ';' && str[i] != '|')
				i++;
		}
	}
	return (wc);
}

static int	init_vars_split(t_split_data *data, char *str)
{
	data->str = str;
	data->k = 0;
	data->start = 0;
	data->end = 0;
	data->wc = count_words(str);
	data->out = (char **)malloc(sizeof(char *) * (data->wc + 1));
	if (!data->out)
		return (-1);
	return (0);
}

//**********MAIN FUNCTION***************/
char	**ft_split_quote(char *str)
{
	t_split_data	data;

	if (init_vars_split(&data, str) == -1)
		return (NULL);
	while (data.str[data.start] != '\0' && data.k < data.wc)
	{
		skip_whitespace(data.str, &data.start);
		data.end = data.start;
		if (data.str[data.start] == '\\' || data.str[data.start] == D_QUOTE)
			skip_quotes(data.str, &data.end);
		else if (data.str[data.start] == ';' || data.str[data.start] == PIPE)
			data.end ++;
		else
		{
			while (data.str[data.end] && (data.str[data.end] != ' ' && \
			data.str[data.end] != '\t' && data.str[data.end] != '\n' \
			&& data.str[data.end] != ';' && data.str[data.end] != '|'))
				data.end++;
		}
		if (data.end > data.start && copy_word(&data) == -1)
			free_split_result_struct(data.out, data.k);
		data.start = data.end;
	}
	data.out[data.k] = NULL;
	return (data.out);
}
