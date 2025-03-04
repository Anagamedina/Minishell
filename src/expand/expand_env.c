/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/04 12:09:09 by anamedin         ###   ########.fr       */
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

char	*extract_variable_name(char *str, size_t *i)
{
	size_t	start;
	char	*var_name;

	start = *i;
	while (str[*i] != '\0' && str[*i] != SPACE && str[*i] != S_QUOTE)
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

char	*expand_variable_replace(char *result, \
		char *var_name, t_list *env_list)
{
	char	*var_value;
	char	*tmp;

	var_value = find_value_in_env(env_list, var_name);
	free(var_name);
	tmp = result;
	if (var_value)
		result = ft_strjoin(result, var_value);
	else
		result = ft_strjoin(result, "");
	free(tmp);
	return (result);
}

char	*append_char_to_result(char *result, char c)
{
	char	*tmp;

	tmp = result;
	result = ft_strjoin_char(result, c);
	free(tmp);
	return (result);
}

char	*replace_dollar_variable_skip_s_quote(char *token_rm_d_quote, \
		t_list *env_list)
{
	char	*result;
	char	*var_name;
	size_t	i;

	if (!token_rm_d_quote || !env_list)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (token_rm_d_quote[i] != '\0')
	{
		if (token_rm_d_quote[i] == DOLLAR_SIGN)
		{
			i++;
			var_name = extract_variable_name(token_rm_d_quote, &i);
			if (!var_name)
				return (free(result), NULL);
			result = expand_variable_replace(result, var_name, env_list);
		}
		else
			result = append_char_to_result(result, token_rm_d_quote[i++]);
	}
	return (result);
}
