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

// Valida y salta comillas correctamente emparejadas
static int validate_and_skip_quotes(const char *str, int *i) {
	char quote;
	int j;

	if (str[*i] == '\'' || str[*i] == '\"') {
		quote = str[*i]; // Tipo de comilla
		(*i)++;          // Saltamos la comilla inicial
		j = *i;

		// Recorremos hasta encontrar la comilla de cierre
		while (str[j] && str[j] != quote) {
			// Si encontramos una comilla diferente dentro, no la consideramos válida
			if ((str[j] == '\'' || str[j] == '\"') && str[j] != quote)
				return (FALSE);
			j++;
		}

		// Si no hay una comilla de cierre, retornamos error
		if (str[j] != quote)
			return (FALSE);

		// Saltamos la comilla de cierre
		*i = j + 1;
		return (TRUE);
	}
	return (FALSE); // No es una comilla
}

// TODO: correginr count_words :(
/*
static int	count_words(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		char tmp = str[i];
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
*/

static int	count_words(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		skip_whitespace(str, &i); // Saltar espacios
		if (str[i] == '\'' || str[i] == '\"')
		{
			// Usar validate_and_skip_quotes para validar y avanzar el índice
			if (validate_and_skip_quotes(str, &i))
				wc++;
			else
				return (-1); // Error: comillas mal emparejadas
		}
		else if (str[i] == ';' || str[i] == '|')
		{
			wc++;
			i++;
		}
		else if (str[i])
		{
			wc++;
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n' \
				&& str[i] != ';' && str[i] != '|')
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
	if (data->wc == -1) {
		printf("Error: comillas no emparejadas.\n");
		return (-1);
	}
	data->out = (char **)malloc(sizeof(char *) * (data->wc + 1));
	if (!data->out)
		return (-1);
	return (0);
}

//**********MAIN FUNCTION***************/

char	**ft_split_quote(char *str) {
	t_split_data data;

	if (init_vars_split(&data, str) == -1)
		return (NULL);

	while (data.str[data.start] != '\0' && data.k < data.wc) {
		skip_whitespace(data.str, &data.start);
		data.end = data.start;

		if (data.str[data.start] == '\'' || data.str[data.start] == '\"') {
			if (!validate_and_skip_quotes(data.str, &data.end)) {
				free_split_result_struct(data.out, data.k);
				return (NULL);
			}
		}
		else if (data.str[data.start] == ';' || data.str[data.start] == '|') {
			data.end++;
		}
		else {
			while (data.str[data.end] && data.str[data.end] != ' ' && \
                  data.str[data.end] != '\t' && data.str[data.end] != '\n' && \
                  data.str[data.end] != ';' && data.str[data.end] != '|')
				data.end++;
		}

		if (data.end > data.start && copy_word(&data) == -1) {
			free_split_result_struct(data.out, data.k);
			return (NULL);
		}

		data.start = data.end;
	}
	data.out[data.k] = NULL;
	return (data.out);
}

// Liberar memoria de los resultados del split
/*
void	free_split_result_struct(char **result, int k) {
	for (int i = 0; i < k; i++)
		free(result[i]);
	free(result);
}
*/
