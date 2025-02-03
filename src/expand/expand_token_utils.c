/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:03:10 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 19:40:14 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_var_name(const char *str)
{
	int		i;
	int		start;
	char	*var_name;

	i = 0;
	start = 0;
	while (str[i] && str[i] == SPACE)
		i ++;
	if (str[i] == DOLLAR_SIGN)
		start = i + 1;
	while (str[i] != '\0' && str[i] != SPACE)
		i ++;
	var_name = malloc(sizeof(char) * (i - start + 1));
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, &str[start], i - start);
	var_name[i - start] = '\0';
	return (var_name);
}

int	update_token_str(t_tokens *token, char **split_word)
{
	char	*new_str;

	new_str = ft_strjoin_array(split_word);
	if (new_str == NULL)
		return (FALSE);
	free(token->str);
	token->str = new_str;
	return (TRUE);
}

void	copy_word_to_token(const char *word, char *merged_token, size_t *k)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0')
	{
		merged_token[*k] = word[i];
		(*k)++;
		i ++;
	}
}

char	*get_and_reconstruct_token(char *split_word, const char *var_val, int i)
{
	int		before;
	int		after;
	int		len_token;
	char	*new_token;

	before = 0;
	while (split_word[i] && split_word[i] == SPACE)
		before ++;
	while (split_word[i] && split_word[i] != SPACE)
		i ++;
	after = 0;
	while (split_word[i] && split_word[i] == SPACE)
		after ++;
	len_token = before + (int) ft_strlen(var_val) + after;
	new_token = malloc(sizeof(char) * (len_token + 1));
	if (!new_token)
		return (NULL);
	ft_memset(new_token, SPACE, before);
	ft_memcpy(new_token + before, var_val, ft_strlen(var_val));
	ft_memset(new_token + before + ft_strlen(var_val), SPACE, after);
	new_token[len_token] = '\0';
	return (new_token);
}

/*
 *ORIGINAL
char	**ft_split_new_version(char *str)
{
	int		i;
	int		j;
	int		k;
	int		wc;
	char	**out;

	i = 0;
	j = 0;
	k = 0;
	wc = 0;
	while (str[i] != '\0')
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i ++;
		if (str[i])
			wc ++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i ++;
	}
	out = (char **) malloc(sizeof(char *) * (wc + 1));
	i = 0;
	while (str[i] != '\0')
	{
		j = i;
		while (str[i] && (str[i] == ' '))
			i ++;
		while (str[i] != '\0' && str[i] != ' ')
			i ++;
		while (str[i] && (str[i] == ' ') && str[i] != '\0')
			i ++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i) + 1));
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}
*/

/*
static int	has_more_than_one_dollar_without_spaces_in_token(const char *str)
{
	int	i;
	int	count_dollar;

	i = 0;
	count_dollar = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DOLLAR_SIGN)
		{
			count_dollar ++;
			if (str[i + 1] == DOLLAR_SIGN)
				return (FALSE);
		}
		i ++;
	}
	if (count_dollar > 1)
		return (TRUE);
	return (FALSE);
}*/