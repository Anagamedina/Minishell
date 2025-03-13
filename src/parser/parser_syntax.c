/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:50:56 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/12 18:50:52 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_syntax_error(char *token)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
}

static int	check_start_and_end_tokens(t_list *token_list)
{
	t_tokens	*first;
	t_tokens	*last;
	t_list		*current;

	current = token_list;
	if (!current)
		return (FALSE);
	first = (t_tokens *)current->content;
	if (first->type_token == PIPE || first->type_token == DELIMITER)
	{
		print_syntax_error(first->str);
		return (FALSE);
	}
	while (current->next)
		current = current->next;
	last = (t_tokens *)current->content;
	if (last->type_token == PIPE || last->type_token == DELIMITER || \
	is_redir(last))
	{
		print_syntax_error(last->str);
		return (FALSE);
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
		if (curr_token->type_token == PIPE && token_list->next)
		{
			next_token = (t_tokens *)token_list->next->content;
			if (is_redir(next_token))
			{
				return (FALSE);
			}
		}
		token_list = token_list->next;
	}
	return (TRUE);
}

int	validate_pipes_and_separators(t_list *token_list)
{
	if (!check_start_and_end_tokens(token_list) || \
			!check_consecutive_operators(token_list))
		return (FALSE);
	return (TRUE);
}

/*int	validate_syntax(t_list *token_list)
{
	if (!check_redir_after_pipe(token_list))
		return (FALSE);
	if (!check_repeated_redirections(token_list) || \
		!validate_pipes_and_separators(token_list))
		return (FALSE);
	return (TRUE);
}*/

int	validate_syntax(t_list *token_list, t_mini *mini)
{
	if (!check_redir_after_pipe(token_list))
	{
		mini->exit_status = 2;
		return (FALSE);
	}
	if (!check_repeated_redirections(token_list) || \
		!validate_pipes_and_separators(token_list))
	{
		mini->exit_status = 2;
		return (FALSE);
	}
	return (TRUE);
}
