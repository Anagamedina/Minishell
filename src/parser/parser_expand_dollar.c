/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:56:02 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/04 12:26:04 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_dollar_occurrences(const char *str)
{
	int	i;
	int	count_dollar;

	i = 0;
	count_dollar = 0;
	if (str[0] == D_QUOTE)
		i = 1;
	while (str[i] != '\0')
	{
		while (str[i] == SPACE)
			i++;
		if (str[i] == DOLLAR_SIGN && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			count_dollar++;
			i++;
			while (str[i] != '\0' && (ft_isalpha(str[i]) || str[i] == '_'))
				i++;
		}
		else if (str[i] == DOLLAR_SIGN && str[i + 1] == ' ')
		{
			count_dollar++;
			i++;
		}
		else
			i++;
	}
	return (count_dollar);
}

int	has_consecutives_env_variables_in_token(t_tokens *token)
{
	if (!token || !token->str)
		return (FALSE);
	if (count_dollar_occurrences(token->str) >= 1)
		return (TRUE);
	return (FALSE);
}


void	handle_consecutive_vars(t_tokens *token, t_list *env_list)
{
	char	*processed_str;
	char	*expanded_str;

	if (!token || !token->str)
		return ;
	processed_str = remove_quotes_str(token->str, D_QUOTE);
	if (!processed_str)
		return ;
	if (processed_str != token->str)
	{
		free(token->str);
		token->str = ft_strdup(processed_str);
	}
	free(processed_str);
	token->length = ft_strlen(token->str);
	expanded_str = expand_consecutives_variables(token, env_list);
	if (!expanded_str)
		return ;
	if (token->str != expanded_str)
	{
		free(token->str);
		token->str = ft_strdup(expanded_str);
	}
	free(expanded_str);
}

/**********MAIN FUNCTION*************/

void	handle_dollar_cases(t_tokens *token, \
								t_list *env_list, t_tokens *next_token)
{
	char	*tmp;
	char	*res;

	if (check_dquote_dollar_and_squotes(token->str))
	{
		remove_and_replace_quotes(token, D_QUOTE);
		return ;
	}
	if (check_dquote_squote_dollar_case(token->str))
	{
		tmp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(tmp);
		res = replace_dollar_variable_skip_s_quote(token->str, env_list);
		token->str = ft_strdup(res);
		free(res);
		return ;
	}
	if (handle_no_expand_cases(token, next_token) == 0)
	{
		tmp = token->str;
		if (has_consecutives_env_variables_in_token(token))
		{
			handle_consecutive_vars(token, env_list);
			if (tmp != token->str)
				tmp = NULL;
		}
		else
			remove_and_replace_quotes(token, D_QUOTE);
	}
}
