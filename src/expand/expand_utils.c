/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/17 17:48:16 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	TODO: daruny (terminar de implementar
//	que si la variable no existe no realizar un strdup de un espacio vacio.
char	*find_value_in_env(t_list *env_list, char *var_name_token)
{
	t_list	*curr_env_list;
	t_env	*curr_env;

	if (!env_list || !var_name_token)
		return (NULL);

	curr_env_list = env_list;
	while (curr_env_list != NULL)
	{
		curr_env = (t_env *)curr_env_list->content;
		if (curr_env->key && (ft_strcmp(var_name_token, curr_env->key) == 0))
		{
			if (curr_env->value != NULL)
				return (ft_strdup(curr_env->value));
			else
				return (NULL);
//			return (ft_strdup(" "));
		}
		curr_env_list = curr_env_list->next;
	}
	return (NULL);
}

void	replace_dollar_variable(char **split_word, t_list *env_list)
{
	char	*var_name;
	char	*var_value;

	if ((*split_word)[0] == DOLLAR_SIGN)
	{
		var_name = ft_strdup(*split_word + 1);
		if (var_name == NULL)
			return ;
		var_value = find_value_in_env(env_list, var_name);

		free(*split_word);
		if (var_value != NULL)
		{
			*split_word = ft_strdup(var_value);
		}
		else
		{
			*split_word = ft_strdup("");
		}
		free(var_name);
		free(var_value);
	}
}

static char	*get_size_split_and_malloc(char **split_word)
{
	size_t	new_len;
	int		i;
	char	*merged_token;

	new_len = 0;
	i = 0;
	while (split_word[i] != NULL)
	{
		new_len += ft_strlen(split_word[i]);
		new_len++;
		i++;
	}
	merged_token = NULL;
	merged_token = (char *)malloc(sizeof(char) * (i + 1));
	if (merged_token == NULL)
		return (NULL);
	merged_token[i] = '\0';
	return (merged_token);
}

void	add_space_if_needed(char **split, size_t i, char *merged, size_t *k)
{
	if (split[i + 1] != NULL)
	{
		merged[*k] = SPACE;
		(*k)++;
	}
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
		add_space_if_needed(split_word, i, merged_token, &k);
		i ++;
	}
	merged_token[k] = '\0';
	return (merged_token);
}
