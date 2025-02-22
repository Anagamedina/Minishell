/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_cases.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:52:31 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/22 18:11:13 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_dollar_case(t_tokens *token, t_list *env_list, \
		char **result, int *i)
{
	int	j;

	(*i)++;
	if (token->str[*i] == '\0' || token->str[*i] == SPACE)
	{
		*result = handle_dollar_alone(*result);
		return ;
	}
	j = *i;
	while (token->str[j] && token->str[j] != DOLLAR_SIGN && \
			token->str[j] != SPACE)
		j++;
	*result = expand_variable(*result, env_list, &token->str[*i], j - *i);
	printf("result: [%s]\n", *result);
	*i = j;
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
