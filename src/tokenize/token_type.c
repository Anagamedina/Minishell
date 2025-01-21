/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/27 11:05:53 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Asigna un tipo de token basado en el valor de la cadena de entrada (por ejemplo, redirección, pipe, palabra, etc.).
int set_token_type(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (REDIR_APPEND);
		//else if (strcmp(str, "<<") == 0)
		//return (HEREDOC);
	else if (strcmp(str, "2>") == 0)
		return (REDIR_ERR_OUT);
	else if (strcmp(str, "2>>") == 0)
		return (REDIR_ERR_APPEND);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, ";") == 0)
		return (DELIMITER);
	else if (str && ft_strlen(str) > 0)
		return (WORD);
	else
		return (NULL_TYPE);
}


/**
 * Verifica si un token es un operador (|, <, > o >>).
 * Esta función categoriza los tokens según si son operadores.
 */
int is_type_of_operator(t_tokens *token)
{
	return (token->type_token == PIPE || \
		token->type_token == REDIR_IN || \
		token->type_token == REDIR_OUT || \
		token->type_token == REDIR_APPEND);
}