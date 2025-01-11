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
		if (str[i] == SEMICOLON || str[i] == PIPE_CHAR)
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

static	int	get_pareja_quote(int *i, const char *str, char c)
{
	(*i)++; // Saltar la primera comilla

	while (str[*i])
	{
		if (str[*i] == c)
		{
			return (*i); // Encontramos la pareja
		}
		(*i)++;
	}
	return (-1);
}

//echo "hello "abc" "
static int	skip_quotes(const char *str, int *i)
{
	char	quote;
	int		pareja;

	quote = str[*i];
	pareja = get_pareja_quote(i, str, quote);

	if (pareja == -1)
	{
		printf("Error: Comillas sin cerrar\n");
		return (FALSE);
	}
	*i = pareja + 1; // Saltar la pareja dle final
	return (TRUE);
}

static void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
		(*i)++;
}

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f')
		return (TRUE);
	return (FALSE);
}

/*
static int	count_words(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i] != '\0')
	{
		skip_whitespace(str, &i);
		if (str[i] == '\0')
			break;
//		if (str[i] == D_QUOTE || str[i] == BACKSLASH || str[i] == S_QUOTE)
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			if (skip_quotes(str, &i))
			{
				wc ++;
			}
		}
		else if (str[i] == SEMICOLON || str[i] == PIPE_CHAR)
		{
			wc ++;
			i ++;
		}
		else
		{
			wc ++;
//			TODO: ver si ispace is allowed library
//			while (str[i] && !isspace(str[i]) && str[i] != SEMICOLON &&
			while (str[i] && !is_whitespace(str[i]) && str[i] != SEMICOLON &&
				   str[i] != PIPE_CHAR && str[i] != D_QUOTE && str[i] != BACKSLASH \
				   && str[i] != S_QUOTE)
			{
				i ++;
			}
		}
	}
	return (wc);
}
*/

static int count_words(char *str)
{
	int i = 0;
	int wc = 0;

	while (str[i] != '\0') {
		skip_whitespace(str, &i);

		if (str[i] == '\0')
			break;

		if (str[i] == D_QUOTE || str[i] == S_QUOTE) {
			if (skip_quotes(str, &i))
				wc++;
		} else if (str[i] == SEMICOLON || str[i] == PIPE_CHAR) {
			wc++;
			i++;
		} else {
			wc++;
			while (str[i] && !is_whitespace(str[i]) &&
				   str[i] != SEMICOLON && str[i] != PIPE_CHAR &&
				   str[i] != D_QUOTE && str[i] != S_QUOTE)
			{
				i ++;
			}
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
	printf("wcs: [%d]\n", data->wc);
	data->out = (char **)malloc(sizeof(char *) * (data->wc + 1));
	if (!data->out)
		return (-1);
	return (0);
}

int	is_special_char(char c)
{
	if(c == SPACE || c == TAB || c == NEWLINE || c == SEMICOLON || c == PIPE_CHAR)
		return (TRUE);
	return (FALSE);
}

//**********MAIN FUNCTION***************/

// echo "hello 'abc '" '  qwer' $USER
// "hello 'abc '" '  qwer' $USER
//	TODO: this case no work well: [   echo ' qwer' $USER   ]

/*
char	**ft_split_quote(char *str)
{
	t_split_data	data;

	if (init_vars_split(&data, str) == -1)
		return (NULL);

	while (data.str[data.start] != '\0' && data.k < data.wc)
	{
		skip_whitespace(data.str, &data.start);
		data.end = data.start;

//		if (data.str[data.start] == BACKSLASH || data.str[data.start] == D_QUOTE)
		if (data.str[data.start] == S_QUOTE || data.str[data.start] == D_QUOTE)
		{
			if (!skip_quotes(data.str, &data.end))
			{
				free_split_result_struct(data.out, data.k);
				return (NULL);
			}
		}
		else if (data.str[data.start] == SEMICOLON || data.str[data.start] == PIPE_CHAR)
			data.end ++;
		else
		{
			while (data.str[data.end] && !is_special_char(data.str[data.end]))
				data.end ++;
		}
		if (data.end > data.start && copy_word(&data) == -1) {
			free_split_result_struct(data.out, data.k);
			return (NULL); // Salida anticipada en caso de error
		}
		data.start = data.end;
	}
	data.out[data.k] = NULL;
	return (data.out);
}
*/

char	**ft_split_quote(char *str)
{
	t_split_data data;

	if (init_vars_split(&data, str) == -1)
		return (NULL);

	while (data.str[data.start] != '\0' && data.k < data.wc)
	{
		skip_whitespace(data.str, &data.start);
		data.end = data.start;

		if (data.str[data.start] == D_QUOTE || data.str[data.start] == S_QUOTE)
		{
			if (!skip_quotes(data.str, &data.end))
			{
				free_split_result_struct(data.out, data.k);
				return (NULL); // Error comillas sin cerrar
			}
		}
		else if (data.str[data.start] == SEMICOLON || data.str[data.start] == PIPE_CHAR)
		{
			data.end++;
		}
		else
		{
			while (data.str[data.end] && !is_special_char(data.str[data.end]))
			{
				// Verificar si estamos dentro de una variable/env seguida por comillas
				if ((data.str[data.end] == '$' &&
					 (data.str[data.end + 1] == D_QUOTE || data.str[data.end + 1] == S_QUOTE)))
				{
					break;
				}
				data.end++;
			}
		}
		if (data.end > data.start && copy_word(&data) == -1)
		{
			free_split_result_struct(data.out, data.k);
			return (NULL); // Salida anticipada en caso de error
		}
		data.start = data.end;
	}
	data.out[data.k] = NULL;
	return (data.out);
}


/*
else
{
while (data.str[data.end] && \
			(data.str[data.end] != SPACE || \
			data.str[data.end] != TAB || \
			data.str[data.end] != NEWLINE || \
			data.str[data.end] != SEMICOLON || \
			data.str[data.end] != PIPE_CHAR))
data.end ++;
}
*/
