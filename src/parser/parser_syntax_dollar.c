/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:08:01 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/16 20:11:05 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	check_special_c(char c)
{
	if (c == '=' || c == ' ' || c == '@' || c == '#' || c == '-' || c == '+' || c == '{'
		|| c == '}' || c == '[' || c == ']' || c == '!' || c == '~' || c == '?'
		|| c == '%' || c == '^' || c == '=' || c == '*' || c == '/' || c == '$'
		|| c == ';' || c == ':' || c == '|' || c == '.' || c == '_' || c == ',')
		return (TRUE);
	return (FALSE);
//	|| c == ';' || c == ':' || c == '|' || c == '<' || c == '>' || c == '\\')
}

void	handle_tokens(t_tokens *token, t_list *env_list, t_tokens* next_token)
{
	char	*tmp;

	tmp = NULL;

	/**
	 * Case single quotes:
	 * @example
	 * Input: echo \'example_token\'
	 * Output: example_token;
	 *
	 * remove comillas simples ('),
	 * verificar con handle_single_quote
	 * Utilizar remove_quotes_str para eliminar squotes.
	 *
	 * TODO: gestionar mas de una sola single quote en un string ??
	 */

	if (handle_single_quote(token))
	{
		tmp = remove_quotes_str(token->str, S_QUOTE);
		token->str = ft_strdup(tmp);
		free(tmp);
		return ;
	}

	/**
	 * Case special quotes:
	 *
	 * Case valid: echo "'$USER hello'"
	 * Case valid: echo " '$USER hello ' "
	 *
	 * Case invalid: echo "" ' $USER ' ""
	 *
	 * gestion de comillas dobles impares(impares expanden las varibales)
	 * Si incluye un dólar ($), se llama a handle_dollar_cases.
	 */

	if (handle_special_quotes(token))
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
		{
			handle_dollar_cases(token, env_list, next_token);
			return ;
		}
		else
		{
			printf("entro en handle_special_quotes cuando es false y no hay $\n");
//			TODO: falta implementar el caso donde no hay $ en el string
			tmp = remove_quotes_str(token->str, D_QUOTE);
			token->str = ft_strdup(tmp);
			free(tmp);
			return ;
		}
	}

	/**
	 * doble comillas son pares :
	 * @example
	 * echo " " '$USER ' " "
	 * echo " "" " '$USER ' " "" "
	 * echo ""'helo $USER 0-9' ""
	 */


//	TODO: modificar para manejar comillas dobles par veces
//	no pudne haber dolar entre d_quotes
//	echo "        "
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

/**
 * Parses and processes tokens for built-in commands followed by words.
 *
 * If the first token is of type `BUILTINS` and followed by `WORD` tokens,
 * it processes each `WORD` token using `handle_tokens` until a non-`WORD`
 *
 * @param mini A pointer to `t_mini` containing:
 *             - `token`: List of tokens to parse.
 *             - `env`: Environment variable list for processing.
 */

/*
void	process_token(t_tokens *curr_token, t_tokens *next_token, t_list *env_list)
{
	if (!next_token)
	{
		handle_tokens(next_token, env_list, NULL);
		return ;
	}
	if (curr_token->type_token == WORD)
	{
		handle_tokens(curr_token, env_list, next_token);
		return ;
    }
}
*/

void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;
	t_tokens	*next_token;

	token_list = mini->token;
	env_list = mini->env;
	if (token_list && \
		((t_tokens *) token_list->content)->type_token == BUILTINS)
		token_list = token_list->next;
	// printf("token_list->content: [%s]\n", ((t_tokens *) token_list->content)->str);
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

/*
void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;
	t_tokens	*next_token;

	token_list = mini->token;
	env_list = mini->env;

	// Validar si la lista de tokens existe y no está vacía
	if (!token_list)
		return;

	// Salta el primer token si es BUILTINS
	if (token_list->content != NULL)
	{
		curr_token = (t_tokens *) token_list->content;
		printf("curr_token->str: [%s]\n", curr_token->str);
		if (curr_token->type_token == BUILTINS)
			token_list = token_list->next;
	}
	// Iterar sobre la lista de tokens
	while (token_list != NULL)
	{
		curr_token = (t_tokens *) token_list->content;
		printf("token->str: [%s]\n", curr_token->str);
		if (token_list->next == NULL)
		{
			handle_tokens(curr_token, env_list, NULL);
		}
		// Verificar si hay un siguiente token antes de acceder a él
		else if (token_list->next != NULL)
		{
			next_token = (t_tokens *) token_list->next->content;
			printf("next_token->str: [%s]\n", next_token->str);
			// Procesar tokens si el actual es de tipo WORD
			if (curr_token->type_token == WORD)
			{
				handle_tokens(curr_token, env_list, next_token);
			}
			else
				break ;
		}
		token_list = token_list->next;
	}
}
*/

/*
void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;
	t_tokens	*next_token;

	token_list = mini->token;
	env_list = mini->env;

	// Salta el primer token si es BUILTINS o CMD_EXTERNAL
	if (token_list != NULL)
	{
		curr_token = (t_tokens *) token_list->content;
		if (curr_token->type_token == BUILTINS)
			token_list = token_list->next;
	}

	while (token_list != NULL)//&& token_list->next != NULL)
	{
		curr_token = (t_tokens *) token_list->content;
		next_token = (t_tokens *) token_list->next->content;

		if (curr_token->type_token == WORD)
			handle_tokens(curr_token, env_list, next_token);
		else
			break;
		token_list = token_list->next;
	}
}
*/





/*void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;
	t_tokens	*next_token;

	token_list = mini->token;
	env_list = mini->env;
	curr_token = (t_tokens *) token_list->content;
	//next_token = (t_tokens *) token_list->next->content;

	if ((curr_token->type_token == BUILTINS) && (token_list->next != NULL) \
		&& (((t_tokens *)(token_list->next->content))->type_token == WORD))
	{
		while (token_list->next != NULL)
		{
			next_token = (t_tokens *) token_list->next->content;
			//curr_token = (t_tokens *)token_list->content;
			if (curr_token->type_token == WORD)
				handle_tokens(curr_token, env_list, next_token);
			else
				break ;
			token_list = token_list->next;
		}
	}
}*/
