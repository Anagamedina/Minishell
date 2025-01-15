/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daruuu <daruuu@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:53:40 by daruuu            #+#    #+#             */
/*   Updated: 2025/01/15 18:53:55 by daruuu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:30 by anamedin          #+#    #+#             */
/*   Updated: 2025/01/14 13:01:12 by  dasalaza        ###   ########.fr       */
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
		{
			return (i);
		}
		i ++;
	}
	return (-1);
}

/**
 * Skips over quoted content in a string.
 *	'asdf'
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
	printf("i: [%d] | open_quote_position: [%c]\n", *i, open_quote_position);

	close_quote_position = find_matching_quote(str, *i, open_quote_position);

	printf("close_quote_position: [%d]\n", close_quote_position);
	printf("i in skip_quotes(): [%d]\n", *i);

	if (close_quote_position == -1)
	{
		printf("Error: Unclosed quotes\n");
		return (FALSE);
	}
	*i = close_quote_position + 1; //  Move past the closing quote
	printf("before exit function(skip_quotes): i: [%d]\n", *i);
	return (TRUE);
}


/*
 * ORIGINAL
static int	skip_quotes(const char *str, int *index)
{
    char opening_quote;

    // Guardar el tipo de comilla (simple o doble)
    opening_quote = str[*index];
    (*index)++; // Saltar la comilla inicial

    // Avanzar hasta encontrar la comilla de cierre correspondiente
    while (str[*index] != '\0')
    {
        // Si encontramos la comilla de cierre
        if (str[*index] == opening_quote)
        {
            return (TRUE); // Éxito: pareja encontrada
        }
        (*index) ++; // Continuar buscando
    }

    // Si no encontramos la comilla de cierre
    printf("Error: Unclosed quote starting at index %d\n", *index);
    return (FALSE);
}
*/

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
			break;

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
	printf("copy_worddddd:\n");
	data->out[data->k] = (char *)malloc(sizeof(char) * \
		(data->end - data->start + 1));

	if (data->out[data->k] == NULL)
		return (-1);
	printf("data->k: [%d]\n", data->k);

	ft_strncpy(data->out[data->k], &data->str[data->start], \
	data->end - data->start);

	data->out[data->k][data->end - data->start] = '\0';
	printf("Token copied: [%s]\n", data->out[data->k]);
	data->k ++;
	return (0);
}

//	**********MAIN FUNCTION***************/

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
				// Verificar si estamos dentro de una variable/env seguida por comillas
				if ((data.str[data.end] == '$' \
					&& (data.str[data.end + 1] == S_QUOTE)))
				{
					data.str[data.end] = ' ';
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
