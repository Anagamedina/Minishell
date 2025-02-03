/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_merge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:17:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 19:19:44 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_size_split_and_malloc(char **split_word)
{
	size_t	new_len;
	int		i;
	char	*merged_token;

	new_len = 0;
	i = 0;
	while (split_word[i] != NULL)
	{
		new_len = ft_strlen(split_word[i]);
		i ++;
	}
	merged_token = (char *)malloc(sizeof(char) * (new_len + 1));
	if (merged_token == NULL)
		return (NULL);
	return (merged_token);
}

char	*ft_strjoin_array(char **split_word)
{
	int		i;
	size_t	k;
	char	*merged_token;

	merged_token = get_size_split_and_malloc(split_word);
	if (merged_token == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (split_word[i] != NULL)
	{
		copy_word_to_token(split_word[i], merged_token, &k);
		i ++;
	}
	merged_token[k] = '\0';
	return (merged_token);
}

char	*ft_strjoin_char(char *str, char c)
{
	char	*result;
	size_t	len;

	len = ft_strlen(str);
	result = NULL;
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	ft_strcpy(result, str);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

/*
static void	add_space_if_needed(char **split, size_t i, char *merged, size_t *k)
{
	if (split[i + 1] != NULL)
	{
		merged[*k] = SPACE;
		(*k)++;
	}
}
*/