/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:30 by anamedin          #+#    #+#             */
/*   Updated: 2025/01/24 11:04:40 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Finds the matching closing quote in a string.
 * Returns TRUE if a matching quote is found, otherwise -1.
 */

int	find_matching_quote(const char *str, int start_index, char quote_char)
{
	int	i;

	i = start_index + 1;
	while (str[i] != '\0')
	{
		if (str[i] == quote_char)
			return (i);
		i ++;
	}
	return (-1);
}

/**
 * Skips over quoted content in a string.
 * checks for a matching closing quote starting from the current
 * position `*index` in the string.
 * If a matching quote is found, it updates
 * index` to point to the position after the closing quote.
 * If no matching quote is found, it prints an error and returns FALSE.
 */

static int	skip_quotes(const char *str, int *i)
{
	char	open_quote_position;
	int		close_quote_position;

	open_quote_position = str[*i];
	close_quote_position = find_matching_quote(str, *i, open_quote_position);
	if (close_quote_position == -1)
		return (FALSE);
	*i = close_quote_position + 1;
	return (TRUE);
}

static void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
		(*i)++;
}

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' \
		|| c == '\v' || c == '\f')
		return (TRUE);
	return (FALSE);
}

int	count_words(const char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i] != '\0')
	{
		skip_whitespace(str, &i);
		if (str[i] == '\0')
			break ;
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			if (skip_quotes(str, &i) == TRUE)
				wc ++;
			else
				break ;
		}
		else if (str[i] == SEMICOLON || str[i] == PIPE_CHAR)
		{
			wc ++;
			i ++;
		}
		else
		{
			wc ++;
			while (str[i] && !is_whitespace(str[i]) && str[i] != ';' && \
			str[i] != '|' && str[i] != '\"' && str[i] != '\'')
				i ++;
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
	printf("wcs in init_vars_split(): [%d]\n", data->wc);
	data->out = (char **) malloc(sizeof(char *) * (data->wc + 1));
	if (!data->out)
		return (FALSE);
	return (TRUE);
}

int	is_special_char(char c)
{
	if (c == SPACE || c == TAB || c == NEWLINE || c == SEMICOLON || c == PIPE_CHAR || c == S_QUOTE || c == D_QUOTE)
		return (TRUE);
	return (FALSE);
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
	data->k ++;
	return (0);
}

//	**********MAIN FUNCTION***************/

/*
 * split[k]:
 * split[0]: "echo"
 * split[1]: " qwerty"
 * split[2]: " hello"
 *
 */

char	**ft_split_quote(char *str)
{
	t_split_data	data;

	if (init_vars_split(&data, str) == FALSE)
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
				return (NULL);
			}
		}
		else if (data.str[data.start] == SEMICOLON || data.str[data.start] == PIPE_CHAR)
			data.end ++;
		else
		{
			while (data.str[data.end] && !is_special_char(data.str[data.end]))
			{
				data.end ++;
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
