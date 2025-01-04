
#include "../../includes/minishell.h"

int	check_special_c(char c)
{
	if (c == '=' || c == '@' || c == '#' || c == '-' || c == '+' || c == '{'
		|| c == '}' || c == '[' || c == ']' || c == '!' || c == '~' || c == '?'
		|| c == '%' || c == '^' || c == '=' || c == '*' || c == '/' || c == '$'
		|| c == ';')
		return (TRUE);
	return (FALSE);
}


void	handle_tokens(t_tokens *token, t_list *env_list)
{
	char	*tmp;

	tmp = NULL;
	if (handle_single_quote(token))
	{
		// if (!handle_no_expand_cases(token))
		// 	expand_dollar(token, env_list);

		tmp = remove_quotes_str(token->str, S_QUOTE);
		token->str = ft_strdup(tmp);
		
		printf("token->str: [%s]\n", token->str);

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
//actualizando tokens de words a builtins o cmd externo
//	actualizando type_token de las words de token list
void	update_words_in_tokens(t_mini *mini)
{
	t_list *token_list;
	t_tokens *curr_token;

	token_list = mini->token;

	// Primera pasada: Clasificar tokens
	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;

		if (curr_token->type_token == WORD)
		{
			printf("Token WORD: %s\n", curr_token->str);
			if (is_builtin_command(curr_token->str))
			{
				curr_token->type_token = BUILTINS;
				printf("Asignado como BUILTINS: %s\n", curr_token->str);
			}
			else if (is_cmd_external(mini, curr_token))
			{
				curr_token->type_token = CMD_EXTERNAL;
				printf("Asignado como CMD_EXTERNAL: %s\n", curr_token->str);
			}
			else
			{
				curr_token->type_token = WORD;
				printf("Asignado como WORD: %s\n", curr_token->str);
			}
		}
		token_list = token_list->next;
	}
}

void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_tokens	*curr_token;

	update_words_in_tokens(mini);
	print_list_token(mini->token);

	// Segunda pasada: Manejar relaciones entre tokens
	token_list = mini->token;
	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;

		if ((curr_token->type_token == BUILTINS || curr_token->type_token == CMD_EXTERNAL) &&
			token_list->next != NULL)
		{
			t_list *next_node = token_list->next;
			t_tokens *next_token = (t_tokens *)next_node->content;

			// Manejar argumentos (tokens de tipo WORD) que siguen al comando
			while (next_token->type_token == WORD)
			{
				handle_tokens(next_token, mini->env);
				next_node = next_node->next;

				if (next_node == NULL)
					break;

				next_token = (t_tokens *)next_node->content;
			}
		}
		token_list = token_list->next;
	}
}