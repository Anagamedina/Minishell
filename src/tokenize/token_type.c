/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/12 18:41:55 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	is_redir_append(t_tokens *token)
{
	return (token->type_token == REDIR_APPEND);
}

int	is_redir_out(t_tokens *token)
{
	return (token->type_token == REDIR_OUT);
}
