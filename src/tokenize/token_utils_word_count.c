/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_word_count.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:49:44 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/12 18:37:05 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quote(char c)
{
	return (c == D_QUOTE || c == S_QUOTE);
}

static int	is_special_char_count_words(char c)
{
	return (c == SEMICOLON || c == PIPE_CHAR);
}

static int	handle_quotes(const char *str, int *i)
{
	if (skip_quotes(str, i))
		return (TRUE);
	return (FALSE);
}

static int	count_word_content(const char *str, int *i)
{
	int	count;

	count = 1;
	while (str[*i] && !is_whitespace(str[*i]) && str[*i] != ';' && \
		str[*i] != '|' && !is_quote(str[*i]))
		(*i)++;
	return (count);
}

int	count_words_split(char *str)
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
		if (is_quote(str[i]))
			wc += handle_quotes(str, &i);
		else if (is_special_char_count_words(str[i]))
		{
			wc ++;
			i ++;
		}
		else
			wc += count_word_content(str, &i);
	}
	return (wc);
}
