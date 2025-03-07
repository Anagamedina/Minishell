/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 18:48:36 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Determines the type of a token based on the input string.
 * @param str The input string to evaluate.
 */

int	set_token_type(char *str)
{
	if (!str || ft_strlen(str) == 0)
		return (NULL_TYPE);
	if (ft_strcmp(str, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (REDIR_APPEND);
	else if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, ";") == 0)
		return (DELIMITER);
	else
		return (WORD);
}

/**
 * chek if a token is an operator (|, <, > o >>).
 * @return TRUE or FALSE
 */

/*
int	is_type_of_operator(t_tokens *token)
{
	return (token->type_token == PIPE || \
		token->type_token == REDIR_IN || \
		token->type_token == REDIR_OUT || \
		token->type_token == REDIR_APPEND || token->type_token == HEREDOC);
}
*/

int	is_builtin_or_external(t_tokens *token)
{
	return (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS);
}

int	is_special_token(t_tokens *token)
{
	return (token->type_token == PIPE || token->type_token == DELIMITER || \
			token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS);
}

int	is_redir(t_tokens *token)
{
	return (token->type_token == REDIR_IN || \
		token->type_token == REDIR_OUT || \
		token->type_token == REDIR_APPEND || token->type_token == HEREDOC);
}

int	is_redir_out(t_tokens *token)
{
	return (token->type_token == REDIR_OUT || \
		token->type_token == REDIR_APPEND);
}
