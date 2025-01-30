/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:52:31 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/29 17:39:44 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//archivo: parser_expand_cases.c


static char	*append_result(char *result, char *to_append)
{
	char	*updated;

	updated = ft_strjoin(result, to_append);
	free(result);
	return (updated);
}

static char	*handle_dollar_alone(char *result)
{
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		return (NULL);
	result = append_result(result, tmp);
	free(tmp);
	return (result);
}

static char	*expand_variable(char *result, \
								t_list *env_list, const char *var, int len)
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

static char	*append_non_dollar_char(char *result, char c)
{
	char	*tmp;

	tmp = ft_substr(&c, 0, 1);
	if (!tmp)
		return (NULL);
	result = append_result(result, tmp);
	free(tmp);
	return (result);
}

static void	handle_dollar_case(t_tokens *token, t_list *env_list, char **result, int *i)
{
	int	j;

	(*i)++;
	if (token->str[*i] == '\0' || token->str[*i] == SPACE)
	{
		*result = handle_dollar_alone(*result);
		return;
	}
	j = *i;
	while (token->str[j] && token->str[j] != DOLLAR_SIGN && token->str[j] != SPACE)
		j++;
	*result = expand_variable(*result, env_list, &token->str[*i], j - *i);
	*i = j;
}

static int	is_valid_input(t_tokens *token, t_list *env_list)
{
	return (token && token->str && env_list);
}



char	*expand_consecutives_variables(t_tokens *token, t_list *env_list)
{
	char	*result;
	int		i;

	if (!is_valid_input(token, env_list))
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (token->str[i] != '\0')
	{
		if (token->str[i] == DOLLAR_SIGN)
			handle_dollar_case(token, env_list, &result, &i);
		else
			result = append_non_dollar_char(result, token->str[i++]);
	}
	return (result);
}