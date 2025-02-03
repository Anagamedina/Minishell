/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:08:29 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 19:52:11 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Counts consecutive pairs of quotes (double or single) in a string.
 * @return The number of consecutive quote pairs found.
 */

int	count_consecutive_quotes(const char *line)
{
	int	i;
	int	consecutive_quotes;
	int	inside_quotes;

	i = 0;
	consecutive_quotes = 0;
	inside_quotes = FALSE;
	while (line[i] != '\0')
	{
		if ((line[i] == D_QUOTE && line[i + 1] == D_QUOTE) || \
			(line[i] == S_QUOTE && line[i + 1] == S_QUOTE && \
			inside_quotes == FALSE))
		{
			consecutive_quotes ++;
			i ++;
		}
		else if (line[i] == D_QUOTE)
			inside_quotes = !inside_quotes;
		i ++;
	}
	return (consecutive_quotes);
}

int	calculate_length_excluding_quotes(char *line)
{
	int	consecutive_quotes;
	int	new_length;

	consecutive_quotes = count_consecutive_quotes(line);
	new_length = ft_strlen(line) - (consecutive_quotes * 2);
	return (new_length);
}

int	skip_quotes_pairs(char *line, int *i, int *start_dquotes, int *end_dquotes)
{
	int	skipped;

	skipped = 0;
	if ((line[*i] == D_QUOTE && line[*i + 1] == D_QUOTE) || \
		(line[*i] == S_QUOTE && line[*i + 1] == S_QUOTE && \
		*start_dquotes == FALSE))
	{
		*i += 2;
		skipped = 1;
	}
	else if (line[*i] == D_QUOTE && *start_dquotes == FALSE)
	{
		*start_dquotes = TRUE;
		*end_dquotes = FALSE;
	}
	else if (*start_dquotes == TRUE && \
		*end_dquotes == FALSE && line[*i] == D_QUOTE)
	{
		*end_dquotes = TRUE;
		*start_dquotes = FALSE;
	}
	return (skipped);
}

void	copy_without_consecutive_quotes(char *line, char *new_line)
{
	int	i;
	int	j;
	int	start_dquotes;
	int	end_dquotes;

	i = 0;
	j = 0;
	start_dquotes = FALSE;
	end_dquotes = FALSE;
	while (line[i] != '\0')
	{
		if (!skip_quotes_pairs(line, &i, &start_dquotes, &end_dquotes))
		{
			new_line[j] = line[i];
			i ++;
			j ++;
		}
	}
	new_line[j] = '\0';
}

/**
 * Removes consecutive quotes (single and double) from a string.
 *
 * @param line The input string.
 * @return A new string without consecutive quotes, or NULL if error memory.
 */

char	*remove_consecutive_quotes(char *line)
{
	char	*new_line;
	int		len;

	if (!line || *line == '\0')
		return (NULL);
	len = calculate_length_excluding_quotes(line);
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	copy_without_consecutive_quotes(line, new_line);
	return (new_line);
}
