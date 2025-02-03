/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 13:09:32 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_value_in_env(t_list *env_list, char *var_name_token)
{
	t_list	*curr_env_list;
	t_env	*curr_env;

	if (!env_list || !var_name_token)
		return (NULL);
	curr_env_list = env_list;
	while (curr_env_list != NULL)
	{
		curr_env = (t_env *) curr_env_list->content;
		if (curr_env->key && (ft_strcmp(var_name_token, curr_env->key) == 0))
		{
			if (curr_env->value != NULL)
				return (ft_strdup(curr_env->value));
			return (NULL);
		}
		curr_env_list = curr_env_list->next;
	}
	return (NULL);
}

/*
static void	replace_dollar_variable(char **split_word, t_list *env_list) {
	char	*var_name;
	char	*var_value;
	int		i;

	i = 0;
	while ((*split_word)[i] != '\0')
	{
		if ((*split_word)[i] == DOLLAR_SIGN)
		{
			var_name = ft_strdup(*split_word + 1);
			if (var_name == NULL)
				return ;
			var_value = find_value_in_env(env_list, var_name);
			free(*split_word);
			if (var_value != NULL)
				*split_word = ft_strdup(var_value);
			else
				*split_word = ft_strdup("");
		}
		else
			i ++;
	}
	free(var_name);
	free(var_value);
}
*/

char	*replace_dollar_variable_skip_s_quote(char *token_rm_d_quote, t_list *env_list)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*tmp;
	size_t	i;
	int		start;

	if (!token_rm_d_quote || !env_list)
		return (NULL);
	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	i = 0;
	while (token_rm_d_quote[i] != '\0')
	{
		if (token_rm_d_quote[i] == DOLLAR_SIGN)
		{
			i ++;
			start = i;
			while (token_rm_d_quote[i] != '\0' && token_rm_d_quote[i] != SPACE && token_rm_d_quote[i] != S_QUOTE)
				i ++;
			var_name = ft_substr(token_rm_d_quote, start, i - start);
			if (var_name == NULL)
			{
				free(result);
				return (NULL);
			}
			var_value = find_value_in_env(env_list, var_name);
			free(var_name);
			tmp = result;
			result = ft_strjoin(result, var_value ? var_value : "");
			free(tmp);
		}
		else
		{
			tmp = result;
			result = ft_strjoin_char(result, token_rm_d_quote[i]);
			free(tmp);
			i ++;
		}
	}
	return (result);
}
