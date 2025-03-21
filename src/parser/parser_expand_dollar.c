/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:56:02 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/08 13:25:32 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_consecutive_vars(t_tokens *token, t_list *env_list)
{
	char	*processed_str;
	char	*expanded_str;

	if (!token || !token->str)
		return ;
	processed_str = remove_quotes_str(token->str, D_QUOTE);
	if (!processed_str)
		return ;
	if (processed_str != token->str)
	{
		free(token->str);
		token->str = ft_strdup(processed_str);
	}
	free(processed_str);
	token->length = ft_strlen(token->str);
	expanded_str = expand_consecutives_variables(token, env_list);
	if (!expanded_str)
		return ;
	if (token->str != expanded_str)
	{
		free(token->str);
		token->str = ft_strdup(expanded_str);
	}
	free(expanded_str);
}

static void	process_dollar_with_quotes(t_tokens *token, t_list *env_list)
{
	char	*tmp;
	char	*res;

	tmp = remove_quotes_str(token->str, D_QUOTE);
	free(token->str);
	token->str = ft_strdup(tmp);
	free(tmp);
	res = replace_dolar_var_skip_s_quote(token->str, env_list);
	free(token->str);
	token->str = ft_strdup(res);
	free(res);
}

void	handle_dolar_case(t_tokens *tk,
						t_list *env_lst, t_tokens *nxt_tkn)
{
	char	*tmp;

	if (check_dquote_dollar_and_squotes(tk->str))
	{
		remove_and_replace_quotes(tk, D_QUOTE);
		return ;
	}
	if (check_dquote_squote_dollar_case(tk->str))
	{
		process_dollar_with_quotes(tk, env_lst);
		return ;
	}
	if (handle_no_expand_cases(tk, nxt_tkn) == 0)
	{
		tmp = tk->str;
		if (has_consecutives_env_variables_in_token(tk))
		{
			handle_consecutive_vars(tk, env_lst);
			if (tmp != tk->str)
				tmp = NULL;
		}
		else
			remove_and_replace_quotes(tk, D_QUOTE);
	}
}
