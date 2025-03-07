/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 19:27:13 by dasalaza         ###   ########.fr       */
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

static char	*extract_var_name_expand(char *token, size_t *i)
{
	size_t	start;
	char	*var_name;

	start = *i;
	while (token[*i] && token[*i] != SPACE && token[*i] != S_QUOTE)
		(*i)++;
	var_name = ft_substr(token, start, *i - start);
	return (var_name);
}

static int	append_variable_value(char **result, t_list *env_lst, char *var_na)
{
	char	*var_value;
	char	*tmp;

	if (!var_na)
	{
		free(*result);
		return (0);
	}
	var_value = find_value_in_env(env_lst, var_na);
	free(var_na);
	tmp = *result;
	if (var_value)
		*result = ft_strjoin(*result, var_value);
	else
		*result = ft_strjoin(*result, "");
	free(tmp);
	if (!*result)
		return (0);
	return (1);
}

/*
static int	append_variable_value(char **result, t_list *env_lst, char *var_nam)
{
	char	*var_value;
	char	*tmp;

	if (!var_nam)
		return (free(*result), 0);
	var_value = find_value_in_env(env_lst, var_nam);
	free(var_nam);
	tmp = *result;
	*result = ft_strjoin(*result, var_value ? var_value : "");
	free(tmp);
	return (*result != NULL);
}
*/

static int	append_char_to_result(char **result, char c)
{
	char	*tmp;

	tmp = *result;
	*result = ft_strjoin_char(*result, c);
	free(tmp);
	return (*result != NULL);
}

char	*replace_dollar_variable_skip_s_quote(char *token, t_list *env_list)
{
	char	*result;
	char	*var_name;
	size_t	i;

	if (!token || !env_list)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (token[i])
	{
		if (token[i] == DOLLAR_SIGN)
		{
			i++;
			var_name = extract_var_name_expand(token, &i);
			if (!append_variable_value(&result, env_list, var_name))
				return (NULL);
		}
		else if (!append_char_to_result(&result, token[i++]))
			return (NULL);
	}
	return (result);
}

/*
char	*replace_dollar_variable_skip_s_quote(char *token_rm_d_quote, \
	t_list *env_list)
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
			while (token_rm_d_quote[i] != '\0' && token_rm_d_quote[i] \
			!= SPACE && token_rm_d_quote[i] != S_QUOTE)
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
*/

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
