/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/16 18:10:37 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_token_type(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (REDIR_INPUT);
	else if (ft_strcmp(str, ">") == 0)
		return (REDIR_OUTPUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (CONCAT_OUTPUT);
	//else if (strcmp(str, "<<") == 0)
		//return (HEREDOC);
	else if (strcmp(str, "2>") == 0)
		return (REDIR_ERR);
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
* Checks if a token is a builtin command.
* - Receives the token string and compares it to supported builtins.
* - Supported builtins: echo, export, unset, env, cd, pwd, exit.
* - Returns TRUE if the token is a builtin, FALSE otherwise.
*/
/*
static int	is_builtin(char *str)
{
	if (!str)
		return (FALSE);
	if (ft_strcmp(str, "echo") == 0)
		return (TRUE);
	if (ft_strcmp(str, "export") == 0)
		return (TRUE);
	if (ft_strcmp(str, "unset") == 0)
		return (TRUE);
	if (ft_strcmp(str, "env") == 0)
		return (TRUE);
	if (ft_strcmp(str, "cd") == 0)
		return (TRUE);
	if (ft_strcmp(str, "pwd") == 0)
		return (TRUE);
	if (ft_strcmp(str, "exit") == 0)
		return (TRUE);
	return (FALSE);
}
*/

int	is_builtin_command(const char *str)
{
	return (strcmp(str, ECHO) == 0 || strcmp(str, EXPORT) == 0 || \
		strcmp(str, UNSET) == 0 || strcmp(str, ENV) == 0 || \
		strcmp(str, CD) == 0 || strcmp(str, PWD) == 0 || \
		strcmp(str, EXIT) == 0);
}

/**
 * Updates the token types in the list if they are builtin commands.
 * - Iterates through each node in `tokens_list`.
 * - If a token is of type WORD and matches a builtin
 * the type is changed to BUILTINS.
 * - Requires each `t_list` node to contain a `t_tokens` struct as content.
 */

void	update_words_to_builtin(t_list *tokens_list)
{
	t_list		*current;
	t_tokens	*curr_token;

	current = tokens_list;
	while (current)
	{
		curr_token = (t_tokens *)current->content;

		if (curr_token->type_token == WORD)
		{
			if (is_builtin_command(curr_token->str))
				curr_token->type_token = BUILTINS;
		}
		current = current->next;
	}
}

/**
 * Update token types to BUILTINS for shell built-ins.
 *
 * Iterates through the token list, and if a token of type `WORD`
 * @param tokens_list Linked list of tokens (t_list).
 * @see after_pipe: Flag para saber si es después de un pipe
 */
void	update_after_pipe_to_builtin(t_list *tokens_list)
{
	t_list		*current;
	int			after_pipe;
	t_tokens	*curr_token;

	current = tokens_list;
	after_pipe = 0;
	while (current)
	{
		curr_token = (t_tokens *)current->content;
		if (curr_token->type_token == PIPE)
			after_pipe = 1;
		else if (after_pipe && curr_token->type_token == WORD)
		{
			if (is_builtin_command(curr_token->str))
				curr_token->type_token = BUILTINS;
			after_pipe = 0;
		}
		current = current->next;
	}
}

//**********MAIN FUNCTION***************/
/**
 * updating their types based on
 * whether they are built-in commands or follow a pipe
 *
 * @param tokens_list Linked list of tokens (t_list).
 * @return TRUE (1) if successful, FALSE (0) if the list is empty.
 */

void	identify_commands(t_list *tokens_list)
{
	update_words_to_builtin(tokens_list);
	update_after_pipe_to_builtin(tokens_list);
}

/*
int	identify_commands(t_list *tokens_list)
{
	t_list		*current;
	t_tokens	*tokens;

	if (!tokens_list)
		return (FALSE);
	current = tokens_list;
	while (current)
	{
		tokens = (t_tokens *)current->content;
		if (tokens->type_token == WORD)
		{
			update_words_to_builtin(tokens_list);
		}
		current = current->next;
	}
	update_after_pipe_to_builtin(tokens_list);
	return (TRUE);
}*/
