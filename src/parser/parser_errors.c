/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:45:45 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 21:19:49 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_syntax_error_token(const char *token_str)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, token_str, ft_strlen(token_str));
	write(2, "'\n", 2);
}

void	print_command_not_found(const char *cmd)
{
	write(2, "bash: ", 6);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
}

void	remove_and_replace_quotes(t_tokens *token, char quote_type)
{
	char	*tmp;

	tmp = remove_quotes_str(token->str, quote_type);
	if (tmp)
	{
		free(token->str);
		token->str = ft_strdup(tmp);
		free(tmp);
	}
}

void	handle_special_cases(t_tokens *token, t_list *env_list, \
		t_tokens *next_token)
{
	if (ft_strchr_true(token->str, DOLLAR_SIGN))
		handle_dollar_cases(token, env_list, next_token);
	else
		remove_and_replace_quotes(token, D_QUOTE);
}
