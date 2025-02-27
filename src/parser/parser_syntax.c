/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:24:43 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/27 13:31:29 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int validate_and_update_words_positions(t_mini *mini)
{
	t_list		*current;
	t_tokens	*prev_token;
	t_tokens	*token;
	int 		command_found;

	if (!mini->tokens)
		return (FALSE);
	current = mini->tokens;
	prev_token = NULL;
	command_found = FALSE;  // Indica si ya hemos encontrado un comando en la línea

	while (current)
	{
		token = (t_tokens *)current->content;

		// Si encontramos una palabra (`WORD`), verificamos su posición
		if (token->type_token == WORD)
		{
			// Si aún no se ha encontrado un comando en la línea actual, es válido
			if (!command_found || !prev_token || prev_token->type_token == PIPE ||
				prev_token->type_token == DELIMITER)
			{
				token->is_valid_cmd = TRUE;  // Es un comando válido
				command_found = TRUE; // Marcamos que ya hay un comando en esta línea
			}
			else
			{
				token->is_valid_cmd = FALSE;  // Se mantiene como argumento
			}
		}
		else if (token->type_token == PIPE || token->type_token == DELIMITER)
		{
			command_found = FALSE;  // Reiniciamos para el siguiente segmento de comandos
		}

		prev_token = token;
		current = current->next;
	}
	return (TRUE);
}



/**
 * Verifica si hay redirecciones repetidas seguidas en la lista de tokens.
 */
int check_repeated_redirections(t_list *token_list)
{
	t_list 		*current;
	t_tokens 	*token;
    t_tokens 	*next_token;

    current = token_list;
	while (current && current->next)
	{
		token = (t_tokens *)current->content;
		next_token = (t_tokens *)current->next->content;

       	if (is_redir(token) && is_redir(next_token))
		{
       		printf("Error: redirecciones repetidas '%s %s'.\n", token->str, next_token->str);
			return (FALSE);
        }
        current = current->next;
	}
	return (TRUE);
}

/**
 * Verifica si hay operadores consecutivos prohibidos (| | o ; ;).
 */
int check_consecutive_operators(t_list *token_list)
{
	t_list 		*current;
	t_tokens 	*token;
	t_tokens 	*prev = NULL;

	current = token_list;

	while (current)
	{
		token = (t_tokens *)current->content;

		// Si hay operadores consecutivos (`| |` o `; ;`), lanzar error
		if (prev && (prev->type_token == PIPE || prev->type_token == DELIMITER) &&
				(token->type_token == PIPE || token->type_token == DELIMITER))
		{
			printf("Error: operadores consecutivos no permitidos '%s' '%s'.\n",
				   prev->str, token->str);
			return (FALSE);
		}

		prev = token;
		current = current->next;
	}
	return (TRUE);
}

/**
 * Verifica si la línea comienza o termina con un operador prohibido.
 */
int check_start_and_end_tokens(t_list *token_list)
{
	t_tokens *first;
	t_tokens *last;
	t_list *current = token_list;

	if (!current)
		return (FALSE);

	// Verificar el primer token
	first = (t_tokens *)current->content;
	if (first->type_token == PIPE || first->type_token == DELIMITER)
	{
		printf("Error: '%s' no puede estar al inicio.\n", first->str);
		return (FALSE);
	}

	// Avanzamos hasta el último token
	while (current->next)
		current = current->next;
	last = (t_tokens *)current->content;

	// Verificar el último token
	if (last->type_token == PIPE || last->type_token == DELIMITER || is_redir(last))
	{
		printf("Error: '%s' no puede estar al final.\n", last->str);
		return (FALSE);
	}
	return (TRUE);
}

/**
 * Valida la posición de `pipes (|)` y `separadores (;)`
 */
int validate_pipes_and_separators(t_list *token_list)
{
	if (!check_start_and_end_tokens(token_list) || !check_consecutive_operators(token_list))
		return (FALSE);
	return (TRUE);
}



/**
 * Valida la sintaxis general de la línea de comandos antes de procesarla.
 */
int validate_syntax(t_list *token_list)
{
	if (!check_repeated_redirections(token_list) ||
		!validate_pipes_and_separators(token_list))
	{
		printf("Error de sintaxis en la entrada.\n");
		return (FALSE);
	}
	return (TRUE);
}