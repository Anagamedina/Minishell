/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:58 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/27 19:10:01 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*int check_start_and_end_tokens(t_list *token_list)
{
	t_tokens *first;
	t_tokens *last;
	t_list *current = token_list;

	if (!current)
		return (FALSE);
	first = (t_tokens *)current->content;
	//inicio
	if (first->type_token == PIPE || first->type_token == DELIMITER)
	{
		printf("Error: '%s' no puede estar al inicio.\n", first->str);
		return (FALSE);
	}
	while (current->next)
		current = current->next;
	last = (t_tokens *)current->content;
	//final
	if (last->type_token == PIPE || last->type_token == DELIMITER || is_redir(last))
	{
		printf("Error: '%s' no puede estar al final.\n", last->str);
		return (FALSE);
	}
	return (TRUE);
}*/

#include <unistd.h>

int check_start_and_end_tokens(t_list *token_list)
{
	t_tokens *first;
	t_tokens *last;
	t_list *current = token_list;

	if (!current)
		return (FALSE);
	first = (t_tokens *)current->content;
	if (first->type_token == PIPE || first->type_token == DELIMITER)
	{
		write(2, "bash: syntax error near unexpected token `", 42);
		write(2, first->str, ft_strlen(first->str));
		write(2, "'\n", 2);
		return (FALSE);
	}
	while (current->next)
		current = current->next;
	last = (t_tokens *)current->content;
	if (last->type_token == PIPE || last->type_token == DELIMITER || is_redir(last))
	{
		write(2, "bash: syntax error near unexpected token `", 42);
		write(2, last->str, ft_strlen(last->str));
		write(2, "'\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

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
			write(2, "bash: syntax error near unexpected token `", 42);
			write(2, next_token->str, ft_strlen(next_token->str));
			write(2, "'\n", 2);
			return (FALSE);
		}
		current = current->next;
	}
	return (TRUE);
}

static void	check_file(t_tokens *curr_next)
{
	int	fd;

	// Si no hay archivo después de '>', error de sintaxis
	if (!curr_next || curr_next->type_token != FILENAME)
	{
		write(2, "bash: syntax error near unexpected token `newline'\n", 51);
		return;
	}

	// Intentar crear el archivo de salida
	fd = open_file(curr_next->str, REDIR_OUT);
	if (fd == -1)
	{
		write(2, "bash: ", 6);
		write(2, curr_next->str, ft_strlen(curr_next->str));
		write(2, ": Permission denied\n", 20); // Puede cambiar según `errno`
	}
	else
		close(fd);
}


/*static void	check_file(t_tokens *curr_token, t_tokens *curr_next)
{
	int	fd;

	if (!curr_next || curr_next->type_token != FILENAME)
	{
		fd = open_file(curr_token->str, REDIR_OUT);
		if (fd == -1)
			perror("Error creando archivo vacío");
		else
			close(fd);
		return;
	}
	fd = open_file(curr_next->str, REDIR_OUT);
	if (fd == -1)
		perror("Error abriendo archivo de SALIDA");
	else
		close(fd);
}*/

void	parse_redir(t_mini *mini)
{
	t_list		*token_list;
	t_tokens	*curr_token;
	t_tokens	*curr_token_next;

	token_list = mini->tokens;
	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;

		if (token_list->next != NULL)
		{
			curr_token_next = (t_tokens *)token_list->next->content;

			// Verificar solo redirecciones de salida `>` o `>>`
			if (is_redir_out(curr_token) && curr_token_next)
				check_file(curr_token_next);
		}
		else if (is_redir_out(curr_token)) // `>` al final de la línea
		{
			write(2, "bash: syntax error near unexpected token `newline'\n", 51);
			return;
		}

		token_list = token_list->next;
	}
}


/*void	parse_redir(t_mini *mini)
{
	t_list		*token_list;
	t_tokens	*curr_token;
	t_tokens	*curr_token_next;

	token_list = mini->tokens;
	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;

		if (token_list->next != NULL)
		{
			curr_token_next = (t_tokens *)token_list->next->content;

			if (is_redir_out(curr_token) == TRUE && curr_token_next->type_token == FILENAME )
				check_file(curr_token, curr_token_next);
		}

		token_list = token_list->next;
	}
}*/