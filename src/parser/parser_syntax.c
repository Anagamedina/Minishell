/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:24:43 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/27 19:16:42 by catalinab        ###   ########.fr       */
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
	command_found = FALSE;

	while (current)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == WORD)
		{
			if (!command_found || !prev_token || prev_token->type_token == PIPE ||
				prev_token->type_token == DELIMITER)
			{
				token->is_valid_cmd = TRUE;
				command_found = TRUE;
			}
			else
				token->is_valid_cmd = FALSE;
		}
		else if (token->type_token == PIPE || token->type_token == DELIMITER)
			command_found = FALSE;
		prev_token = token;
		current = current->next;
	}
	return (TRUE);
}

int check_consecutive_operators(t_list *token_list)
{
	t_list 		*current;
	t_tokens 	*token;
	t_tokens 	*prev = NULL;

	current = token_list;

	while (current)
	{
		token = (t_tokens *)current->content;
		if (prev && (prev->type_token == PIPE || prev->type_token == DELIMITER) &&
				(token->type_token == PIPE || token->type_token == DELIMITER))
		{
			write(2, "bash: syntax error near unexpected token `", 42);
			write(2, token->str, ft_strlen(token->str));
			write(2, "'\n", 2);
			return (FALSE);
		}
		if (prev && is_redir(prev) && token->type_token == PIPE)
		{
			write(2, "bash: syntax error near unexpected token `|'\n", 45);
			return (FALSE);
		}
		prev = token;
		current = current->next;
	}
	return (TRUE);
}


static int	check_redir_after_pipe(t_list *token_list)
{
	t_tokens	*curr_token;
	t_tokens	*next_token;

	while (token_list)
	{
		curr_token = (t_tokens *)token_list->content;

		// Si encontramos un `|`, verificamos el siguiente token
		if (curr_token->type_token == PIPE && token_list->next)
		{
			next_token = (t_tokens *)token_list->next->content;

			if (is_redir(next_token))
			{
				//write(2, "bash: syntax error near unexpected token `", 42);
				//write(2, next_token->str, ft_strlen(next_token->str));
				//write(2, "'\n", 2);
				return (FALSE);
			}
		}
		token_list = token_list->next;
	}
	return (TRUE);
}



int validate_pipes_and_separators(t_list *token_list)
{
	if (!check_start_and_end_tokens(token_list) || !check_consecutive_operators(token_list))
		return (FALSE);
	return (TRUE);
}

/*int validate_syntax(t_list *token_list)
{
	if (!check_repeated_redirections(token_list) ||
		!validate_pipes_and_separators(token_list))
	{
		return (FALSE);
	}
	return (TRUE);
}*/

int validate_syntax(t_list *token_list)
{
	//Primero, verificamos `| < file.txt`
	if (!check_redir_after_pipe(token_list))
		return (FALSE);
	if (!check_repeated_redirections(token_list) ||
		!validate_pipes_and_separators(token_list))
	{
		return (FALSE);
	}
	return (TRUE);
}



















/*void init_validation_vars(t_mini *mini, t_list **current,
						  t_tokens **prev_token, int *command_found)
{
	*current = mini->tokens;
	*prev_token = NULL;
	*command_found = FALSE;
}

void update_token_status(t_tokens *token, t_tokens *prev_token, int *command_found)
{
	if (token->type_token == WORD)
	{
		if (!*command_found || !prev_token || prev_token->type_token == PIPE ||
			prev_token->type_token == DELIMITER)
		{
			token->is_valid_cmd = TRUE;
			*command_found = TRUE;
		}
		else
			token->is_valid_cmd = FALSE;
	}
	else if (token->type_token == PIPE || token->type_token == DELIMITER)
		*command_found = FALSE;
}

int validate_and_update_words_positions(t_mini *mini)
{
	t_list		*current;
	t_tokens	*prev_token;
	t_tokens	*token;
	int 		command_found;

	if (!mini->tokens)
		return (FALSE);
	init_validation_vars(mini, &current, &prev_token, &command_found);
	while (current)
	{
		token = (t_tokens *)current->content;
		update_token_status(token, prev_token, &command_found);
		prev_token = token;
		current = current->next;
	}
	return (TRUE);
}*/