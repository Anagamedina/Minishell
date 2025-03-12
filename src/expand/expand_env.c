/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/09 21:57:03 by dasalaza         ###   ########.fr       */
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
	{
		*result = ft_strjoin(*result, var_value);
		free(var_value);
	}
	else
		*result = ft_strjoin(*result, "");
	free(tmp);
	if (!*result)
		return (0);
	return (1);
}

static int	append_char_to_result(char **result, char c)
{
	char	*tmp;

	tmp = *result;
	*result = ft_strjoin_char(*result, c);
	free(tmp);
	return (*result != NULL);
}

//TODO:	posible leak en esta funcion
char	*replace_dolar_var_skip_s_quote(char *tk_update, t_list *env_list)
{
	char	*result;
	char	*var_name;
	size_t	i;

	if (!tk_update || !env_list)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (tk_update[i])
	{
		if (tk_update[i] == DOLLAR_SIGN)
		{
			i++;
			var_name = extract_var_name_expand(tk_update, &i);
			if (!append_variable_value(&result, env_list, var_name))
			{
				return (free(result), NULL);
			}
		}
		else if (!append_char_to_result(&result, tk_update[i++]))
			return (free(result), NULL);
	}
	return (result);
}
