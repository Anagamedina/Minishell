/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:08:01 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/22 17:27:01 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	check_special_c(char c)
{
	if (c == '=' || c == ' ' || c == '@' || c == '#' || c == '-' || c == '+' \
		|| c == '{' || c == '}' || c == '[' || c == ']' || c == '!' \
		|| c == '~' || c == '?' || c == '%' || c == '^' || c == '=' \
		|| c == '*' || c == '/' || c == '$' || c == ';' || c == ':' \
		|| c == '|' || c == '.' || c == '_' || c == ',')
	{
		return (TRUE);
	}
	return (FALSE);
}

void	handle_tokens(t_tokens *token, t_list *env_list, t_tokens *next_token)
{
	char	*tmp;

	tmp = NULL;

	/**
     * Case: Single quotes(' ')
     * - Removes single quotes from the token string.
     * @example: [echo 'example_token'] -> [example_token]
	 * TODO: gestionar mas de una sola single quote en un string
	 * TODO: update name function: process_single_quotes
	 */

	if (handle_single_quote(token))
	{
		tmp = remove_quotes_str(token->str, S_QUOTE);
		free(token->str);
		token->str = ft_strdup(tmp);
		// free(tmp);
		return ;
	}

	/**
     * Case: Special quotes (" '...' '...' $VAR")
     * - Expands variables if `$` is present within uneven double quotes.
     * @example: [echo "'$USER hello'"] -> [username hello]
     * TODO: update name function: process_special_quotes
     */
	if (handle_special_quotes(token))
	{
		// if found $ in the string
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
		{
			handle_dollar_cases(token, env_list, next_token);
			return ;
		}
		else
		{
			printf("entra en handle_special_quotes when not found $ :)\n");
			//	TODO: Handle double quotes without `$` properly.
			//	TODO: falta implementar el caso donde no hay $ en el string
			tmp = remove_quotes_str(token->str, D_QUOTE);
			
			free(token->str);
			token->str = ft_strdup(tmp);
			free(tmp);
			return ;
		}
	}

	/**
     * Case: Even double quotes ("..." "...")
     * - Handles cases where double quotes are even.
     * @example: [echo " '$USER ' "] -> [ '$USER ' ]
     */

	if (has_even_double_quotes(token))
	{
		handle_dollar_cases(token, env_list, next_token);
		return ;
	}

	/**
     * Case: Variables outside quotes
     * - Expands variables if `$` is present.
     */
	if (ft_strchr_true(token->str, DOLLAR_SIGN))
	{
		handle_dollar_cases(token, env_list, next_token);
		return ;
	}
}


//	actualizando tokens de words a builtins o cmd externo
//	actualizando type_token de las words de token list
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
			printf("Token WORD: %s\n", curr_token->str);
			if (is_builtin_command(curr_token->str))
			{
				curr_token->type_token = BUILTINS;
			}
			else if (is_cmd_external(mini, curr_token))
			{
				curr_token->type_token = CMD_EXTERNAL;
			}
			else
			{
				curr_token->type_token = WORD;
			}
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

/*
 *original ana
void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_tokens	*curr_token;

	update_words_in_tokens(mini);
	//print_list_token(mini->token);

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
*/
