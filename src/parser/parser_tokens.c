
#include "../../includes/minishell.h"

//se pude poner en una funcion esta parte:
//porque veo que se repite varias veces.

/*
 * void	remove_and_replace_quotes(t_tokens *token, char quote_type)
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

 void	handle_tokens(t_tokens *token, t_list *env_list, t_tokens *next_token)
{
	if (handle_single_quote(token))
	{
		remove_and_replace_quotes(token, S_QUOTE);
		return;
	}

	if (handle_special_quotes(token))
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
		{
			handle_dollar_cases(token, env_list, next_token);
			return;
		}
		else
		{
			remove_and_replace_quotes(token, D_QUOTE);
			return;
		}
	}

	if (has_even_double_quotes(token))
	{
		handle_dollar_cases(token, env_list, next_token);
		return;
	}

	if (ft_strchr_true(token->str, DOLLAR_SIGN))
	{
		handle_dollar_cases(token, env_list, next_token);
		return;
	}
}


 * */
void	handle_tokens(t_tokens *token, t_list *env_list, t_tokens *next_token)
{
	char	*tmp;

	tmp = NULL;

	if (handle_single_quote(token))
	{
		tmp = remove_quotes_str(token->str, S_QUOTE);
		free(token->str);
		token->str = ft_strdup(tmp);
		// free(tmp);
		return ;
	}

	if (handle_special_quotes(token))
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
		{
			handle_dollar_cases(token, env_list, next_token);
			return ;
		}
		else
		{
			tmp = remove_quotes_str(token->str, D_QUOTE);
			free(token->str);
			token->str = ft_strdup(tmp);
			free(tmp);
			return ;
		}
	}

	if (has_even_double_quotes(token))
	{
		handle_dollar_cases(token, env_list, next_token);
		return ;
	}
	if (ft_strchr_true(token->str, DOLLAR_SIGN))
	{
		handle_dollar_cases(token, env_list, next_token);
		return ;
	}
}


void	update_words_in_tokens(t_mini *mini)
{
	t_list *token_list;
	t_tokens *curr_token;

	token_list = mini->token;

	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;

		if (curr_token->type_token == WORD)
		{
			if (is_builtin_command(curr_token->str))
				curr_token->type_token = BUILTINS;
			else if (is_cmd_external(mini, curr_token))
				curr_token->type_token = CMD_EXTERNAL;
			else
				curr_token->type_token = WORD;
		}
		token_list = token_list->next;
	}
}


void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;
	t_tokens	*next_token;

	update_words_in_tokens(mini);

	token_list = mini->token;
	env_list = mini->env;

	if (token_list && (((t_tokens *) token_list->content)->type_token == BUILTINS || \
		((t_tokens *) token_list->content)->type_token == CMD_EXTERNAL))
		token_list = token_list->next;

	while (token_list != NULL)
	{
		curr_token = (t_tokens *) token_list->content;
		if (token_list->next != NULL)
			next_token = (t_tokens *) token_list->next->content;
		else
			next_token = NULL;
		if (curr_token->type_token == WORD)
			handle_tokens(curr_token, env_list, next_token);
		else
			break ;
		token_list = token_list->next;
	}
}




//COPIA 

/**void	handle_tokens(t_tokens *token, t_list *env_list, t_tokens *next_token)
{
	char	*tmp;

	tmp = NULL;

	if (handle_single_quote(token))
	{
		tmp = remove_quotes_str(token->str, S_QUOTE);
		free(token->str);
		token->str = ft_strdup(tmp);
		// free(tmp);
		return ;
	}

	if (handle_special_quotes(token))
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
		{
			handle_dollar_cases(token, env_list, next_token);
			return ;
		}
		else
		{
			tmp = remove_quotes_str(token->str, D_QUOTE);
			free(token->str);
			token->str = ft_strdup(tmp);
			free(tmp);
			return ;
		}
	}

	if (has_even_double_quotes(token))
	{
		handle_dollar_cases(token, env_list, next_token);
		return ;
	}
	if (ft_strchr_true(token->str, DOLLAR_SIGN))
	{
		handle_dollar_cases(token, env_list, next_token);
		return ;
	}
} */