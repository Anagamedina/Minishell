/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:29:45 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/19 16:30:41 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_special_c(char c)
{
	if (c == '=' || c == ' ' || c == '@' || c == '#' || c == '-' || c == '+' \
		|| c == '{' || c == '}' || c == '[' || c == ']' || c == '!' \
		|| c == '~' || c == '?' || c == '%' || c == '^' || c == '=' \
		|| c == '*' || c == '/' || c == '$' || c == ';' || c == ':' \
		|| c == '|' || c == '.' || c == '_' || c == ',')
	{
		return (TRUE);
	}
	return (FALSE);
}

int	has_dollar_with_only_spaces_or_only_dollar(const char *str)
{
	return (
		(str[0] != '\0' && str[0] == '"' && str[1] != '\0' && str[1] == '$' \
		&& str[2] != '\0' && str[2] == ' ') || \
		(str[0] != '\0' && str[0] == '"' && str[1] != '\0' && str[1] == '$'));
}

static int	count_new_length(const char *str, char quote_char)
{
	int	i;
	int	new_len;

	i = 0;
	new_len = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != quote_char && (str[i] >= 31 && str[i] <= 126)) \
			|| check_special_c(str[i]) == TRUE)
			new_len++;
		i++;
	}
	return (new_len);
}

static void	copy_without_quotes(const char *str, char *new_str, char quote_char)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != quote_char && (str[i] >= 31 && str[i] <= 126)) \
			|| check_special_c(str[i]) == TRUE)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
}

char	*remove_quotes_str(const char *str, char quote_char)
{
	int		new_len;
	char	*new_str;

	if (!str)
		return (NULL);
	new_len = count_new_length(str, quote_char);
	new_str = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new_str)
		return (NULL);
	copy_without_quotes(str, new_str, quote_char);
	return (new_str);
}
