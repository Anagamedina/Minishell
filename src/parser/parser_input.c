/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:58 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/12 18:49:52 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_repeated_redirections(t_list *token_list)
{
	t_list		*current;
	t_tokens	*token;
	t_tokens	*next_token;

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

static void	check_file_out(t_tokens *curr_next)
{
	int	fd;

	if (!curr_next || curr_next->type_token != FILENAME)
	{
		write(2, "bash: syntax error near unexpected token `newline'\n", 51);
		return ;
	}
	fd = open_file(curr_next->str, REDIR_OUT);
	if (fd == -1)
	{
		write(2, "bash: ", 6);
		write(2, curr_next->str, ft_strlen(curr_next->str));
		write(2, ": No such file or directory\n", 28);
	}
	else
		close(fd);
}

static void	check_file_append(t_tokens *curr_next)
{
	int	fd;

	if (!curr_next || curr_next->type_token != FILENAME)
	{
		write(2, "bash: syntax error near unexpected token `newline'\n", 51);
		return ;
	}
	fd = open_file(curr_next->str, REDIR_APPEND);
	if (fd == -1)
	{
		write(2, "bash: ", 6);
		write(2, curr_next->str, ft_strlen(curr_next->str));
		write(2, ": No such file or directory\n", 28);
	}
	else
		close(fd);
}

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
			if (is_redir_append(curr_token) && curr_token_next)
				check_file_append(curr_token_next);
			if (is_redir_out(curr_token) && curr_token_next)
				check_file_out(curr_token_next);
		}
		else if (is_redir_out(curr_token))
		{
			write(2, "bash: syntax error near unexpected token `", 42);
			write(2, "newline'\n", 9);
			return ;
		}
		token_list = token_list->next;
	}
}
