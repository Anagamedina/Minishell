/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle_not_expand.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:21:18 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/19 16:21:29 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_backslash_after_dollar(t_tokens *token)
{
	char	*temp;

	temp = remove_quotes_str(token->str, D_QUOTE);
	token->str = ft_strdup(temp + 1);
	if (!token->str)
	{
		perror("error: ft_strdup failed");
		return (FALSE);
	}
	return (TRUE);
}

int	handle_one_digit_after_dollar(t_tokens *token)
{
	free(token->str);
	token->str = ft_strdup("");
	return (TRUE);
}

int	handle_digit_and_more_after_dollar(t_tokens *token)
{
	char	*temp;

	if (token->str[0] == D_QUOTE && token->str[token->length - 1] == D_QUOTE)
	{
		temp = remove_quotes_str(token->str, D_QUOTE);
		token->str = ft_strdup(temp);
		temp = NULL;
	}
	temp = ft_strdup(token->str + 2);
	if (!temp)
	{
		perror("error: strdup");
		exit(EXIT_FAILURE);
	}
	free(token->str);
	token->str = temp;
	return (TRUE);
}
