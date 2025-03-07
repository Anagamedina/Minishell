/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:12:21 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 20:28:11 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*append_result(char *result, char *to_append)
{
	char	*updated;

	if (!result)
		result = ft_strdup("");
	if (!result || !to_append)
		return (NULL);
	updated = ft_strjoin(result, to_append);
	free(result);
	return (updated);
}

char	*handle_dollar_alone(char *result)
{
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		return (NULL);
	result = append_result(result, tmp);
	free(tmp);
	return (result);
}

char	*expand_variable(char *result, t_list *env_list, \
		const char *var, int len)
{
	char	*tmp;
	char	*expanded_value;

	tmp = ft_substr(var, 0, len);
	if (tmp == NULL)
		return (NULL);
	expanded_value = find_value_in_env(env_list, tmp);
	free(tmp);
	if (expanded_value)
	{
		result = append_result(result, expanded_value);
		free(expanded_value);
	}
	else
		result = append_result(result, " ");
	return (result);
}

char	*append_non_dollar_char(char *result, char c)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_substr(&c, 0, 1);
	if (!tmp)
		return (NULL);
	result = append_result(result, tmp);
	free(tmp);
	return (result);
}

int	is_valid_input(t_tokens *token, t_list *env_list)
{
	return (token && token->str && env_list);
}
