/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:04:14 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/26 00:27:36 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:20:25 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/24 16:26:33 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_vars_split(t_split_data *data, char *str)
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

void	process_word(t_split_data *data)
{
	while (data->str[data->end] && !is_special_char(data->str[data->end]))
		data->end++;
}

int	process_segment(t_split_data *data)
{
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
	if (data->end > data->start && copy_word(data) == -1)
		return (0);
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
		if (!process_segment(&data))
		{
			free_split_result_struct(data.out, data.k);
			return (NULL);
		}
	}
	data.out[data.k] = NULL;
	return (data.out);
}
