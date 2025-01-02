
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


void parser_tokens(t_mini *mini)
{
	t_list *token_list;
	t_list *env_list;
	t_tokens *curr_token;

	token_list = mini->token;
	env_list = mini->env;

	// Itera a través de los tokens y asigna el tipo adecuado
	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;
		//assign_token_type(curr_token, mini->exec);

		// Si el primer token es un comando builtin y hay un siguiente token de tipo WORD
		if ((curr_token->type_token == BUILTINS || curr_token->type_token == CMD_EXTERNAL) && (token_list->next != NULL))
		{
			curr_token = (t_tokens *)token_list->next->content;
			if (curr_token->type_token == WORD)
			{
				// Aquí manejamos los tokens de tipo WORD que siguen a los comandos BUILTINS
				while (token_list->next != NULL)
				{
					curr_token = (t_tokens *)token_list->next->content;
					if (curr_token->type_token == WORD)
					{
						handle_tokens(curr_token, env_list); // Función que maneja los tokens de tipo WORD
					}
					else
					{
						break; // Rompe el bucle si el token no es de tipo WORD
					}
					token_list = token_list->next;
				}
			}
		}

		token_list = token_list->next; // Avanza al siguiente token
	}
}
