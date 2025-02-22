/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:04:14 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 18:52:06 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_vars_split(t_split_data *data, char *str)
{
	data->out = NULL;
	data->str = str;
	data->k = 0;
	data->start = 0;
	data->end = 0;
	data->wc = count_words_split(str);
	data->out = (char **) malloc(sizeof(char *) * (data->wc + 1));
	if (!data->out)
		return (FALSE);
	return (TRUE);
}

int	copy_word(t_split_data *data)
{
	int	word_length;

	word_length = data->end - data->start;
	if (word_length <= 0)
	{
		return (-1);
	}
	data->out[data->k] = (char *) malloc(sizeof(char) * (word_length + 1));
	if (!data->out[data->k])
	{
		free_split_result_struct(data->out, data->k);
		free(data->out);
		return (-1);
	}
	ft_strncpy(data->out[data->k], &data->str[data->start], word_length);
	data->out[data->k][word_length] = '\0';
	data->k++;
	return (0);
}

void	process_word(t_split_data *data)
{
	while (data->str[data->end] && !is_special_char(data->str[data->end]))
		data->end++;
}

int	process_segment(t_split_data *data)
{
	int	result_copy_word;

	result_copy_word = 0;
	data->end = data->start;
	if (is_quote(data->str[data->start]))
	{
		if (!skip_quotes(data->str, &data->end))
			return (0);
	}
	else if (is_special_char(data->str[data->start]))
		data->end++;
	else
		process_word(data);
	result_copy_word = copy_word(data);
	if (data->end > data->start)
	{
		if (result_copy_word == -1)
		{
			free_split_result_struct(data->out, data->k);
			free(data->out);
			return (0);
		}
	}
	data->start = data->end;
	return (TRUE);
}

//	**********MAIN FUNCTION***************/
/**
 * splits a string into an array of substrings,
 * considering quotes and special characters.
 */
char	**ft_split_quotes(char *str)
{
	t_split_data	data;

	if (init_vars_split(&data, str) == FALSE)
		return (NULL);
	while (data.str[data.start] != '\0' && data.k < data.wc)
	{
		skip_whitespace(data.str, &data.start);
		if (process_segment(&data) == 0)
		{
			free_split_result_struct(data.out, data.k);
			free(data.out);
			return (NULL);
		}
	}
	data.out[data.k] = NULL;
	return (data.out);
}