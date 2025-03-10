/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 17:30:37 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	is_type_of_operator(t_tokens *token)
{
	return (token->type_token == PIPE || \
		token->type_token == REDIR_IN || \
		token->type_token == REDIR_OUT || \
		token->type_token == REDIR_APPEND || token->type_token == HEREDOC);
}

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

// int	is_redir_out(t_tokens *token)
// {
// 	return (token->type_token == REDIR_OUT ||cat << EOF > heredoc_test.txt 
// 		token->type_token == REDIR_APPEND);
// }
int	is_redir_append(t_tokens *token)
{
	return (token->type_token == REDIR_APPEND);
}

int	is_redir_out(t_tokens *token)
{
	return (token->type_token == REDIR_OUT);
}
