/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:30 by anamedin          #+#    #+#             */
/*   Updated: 2025/01/24 14:01:58 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Finds the matching closing quote in a string.
 * Returns TRUE if a matching quote is found, otherwise -1.
 */

static int	find_match_quote(const char *str, int start_index, char quote_char)
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
 * If a matching quote is found, it updates
 * index` to point to the position after the closing quote.
 * If no matching quote is found, it prints an error and returns FALSE.
 */

int	skip_quotes(const char *str, int *i)
{
	char	open_quote_position;
	int		close_quote_position;

	open_quote_position = str[*i];
	close_quote_position = find_match_quote(str, *i, open_quote_position);
	if (close_quote_position == -1)
		return (FALSE);
	*i = close_quote_position + 1;
	return (TRUE);
}

void	skip_whitespace(const char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
		(*i)++;
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' \
		|| c == '\v' || c == '\f')
		return (TRUE);
	return (FALSE);
}

int	is_special_char(char c)
{
	if (c == SPACE || c == TAB || c == NEWLINE || c == SEMICOLON \
		|| c == PIPE_CHAR || c == S_QUOTE || c == D_QUOTE)
		return (TRUE);
	return (FALSE);
}
