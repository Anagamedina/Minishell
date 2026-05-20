/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:03:10 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/12 19:20:46 by dasalaza         ###   ########.fr       */
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

char	*get_and_reconstruct_token(char *split_wrd, char *var_val, int i)
{
	int		before;
	int		after;
	int		len_token;
	char	*new_token;
	int		var_len;

	before = 0;
	var_len = 0;
	if (var_val)
		var_len = (int)ft_strlen(var_val);
	while (split_wrd[i] && split_wrd[i] == SPACE)
		before ++;
	while (split_wrd[i] && split_wrd[i] != SPACE)
		i ++;
	after = 0;
	while (split_wrd[i] && split_wrd[i] == SPACE)
		after ++;
	len_token = before + var_len + after;
	new_token = malloc(sizeof(char) * (len_token + 1));
	if (!new_token)
		return (NULL);
	ft_memset(new_token, SPACE, before);
	if (var_val)
		ft_memcpy(new_token + before, var_val, var_len);
	ft_memset(new_token + before + var_len, SPACE, after);
	new_token[len_token] = '\0';
	return (new_token);
}
