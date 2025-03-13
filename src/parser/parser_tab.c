/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:26:11 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/13 01:13:02 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	calculate_result_size(const char *str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == BACKSLASH && str[i + 1])
			i ++;
		len++;
		i++;
	}
	return (len);
}

void	process_string(const char *str, char *result)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == BACKSLASH && str[i + 1])
		{
			if (str[i + 1] == 'n')
				result[j++] = '\n';
			else if (str[i + 1] == 't')
				result[j++] = '\t';
			else
				result[j++] = str[i + 1];
			i += 2;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
}

char	*convert_escape_sequences(const char *str)
{
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	len = calculate_result_size(str);
	result = malloc(len + 1);
	if (!result)
	{
		return (NULL);
	}
	process_string(str, result);
	return (result);
}

int	handle_single_quotes_after_dollar(t_tokens *token)
{
	char	*temp;
	char	*processed_str;

	processed_str = remove_quotes_str(token->str, S_QUOTE);
	if (!processed_str)
	{
		return (FALSE);
	}
	temp = convert_escape_sequences(processed_str);
	free(processed_str);
	if (!temp)
	{
		return (FALSE);
	}
	free(token->str);
	token->str = ft_strdup(temp);
	free(temp);
	if (!token->str)
	{
		return (FALSE);
	}
	return (TRUE);
}
