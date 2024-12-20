
#include "../../includes/minishell.h"

void	handle_tokens(t_tokens *token, t_list *env_list)
{
	char	*tmp;

	tmp = NULL;
	if (handle_single_quote(token))
	{
		tmp = remove_quotes_str(token->str, S_QUOTE);
		token->str = ft_strdup(tmp);
		return ;
	}
	if (handle_special_quotes(token))
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
		{
			handle_dollar_cases(token, env_list);
			return ;
		}
	}
	if (handle_double_quotes(token))
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
		{
			handle_dollar_cases(token, env_list);
			return ;
		}
	}
	if (ft_strchr_true(token->str, DOLLAR_SIGN))
	{
		handle_dollar_cases(token, env_list);
		return ;
	}
}

void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;

	token_list = mini->token;
	env_list = mini->env;
	curr_token = (t_tokens *) token_list->content;

	if ((curr_token->type_token == BUILTINS) && (token_list->next != NULL) \
		&& (((t_tokens *)(token_list->next->content))->type_token == WORD))
	{
		while (token_list->next != NULL)
		{
			curr_token = (t_tokens *)token_list->next->content;
			if (curr_token->type_token == WORD)
				handle_tokens((t_tokens *) curr_token, env_list);
			else
				break ;
			token_list = token_list->next;
		}
	}
}