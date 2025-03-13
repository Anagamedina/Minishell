/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:45:45 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/12 19:18:35 by dasalaza         ###   ########.fr       */
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

void	handle_special_cases(t_tokens *tok, t_list *env, t_tokens *nxt_tok)
{
	if (ft_strchr_true(tok->str, DOLLAR_SIGN))
		handle_dolar_case(tok, env, nxt_tok);
	else
		remove_and_replace_quotes(tok, D_QUOTE);
}
