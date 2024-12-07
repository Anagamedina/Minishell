//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"

//void handle_single_quote(t_tokens *token);


/*
function auxiliar que verifique sintaxis de VAR $
		$[a-zA-Z][a-zA-Z0-9]*
		$[a-zA-Z][a-zA-Z0-9]*
 gestionar que el $ siempre al principio del str
 echo $_ a-zA-Z
*/
static int syntax_var_dollar(char *str)
{
	int i;

	if (!(ft_isalpha(str[0])) || ft_isdigit(str[0]))
		return (FALSE);
	i = 1;
	while (str[i] != '\0')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

//iterar por cada argumento de cada comando y 
// le pasamos una funcion auxiliar de syntaxis
//verificar que contiene un $ 

int	check_dollar_in_token(t_tokens *tokens_list)
{
	t_tokens 		*token_current;
	int 			found_dollar;

	found_dollar = 0;
	token_current = (t_tokens *)tokens_list;
	while (token_current != NULL)
	{
		if (syntax_var_dollar((char *)token_current) == 1)
		{
			found_dollar = 1;
		}
		token_current = token_current->next;
	}
	return (found_dollar);
}

/**
 * this function
 * check if a WORD contains a $ and expand it
 *
 */

void	parser_tokens(t_mini *mini)
{
	t_list	*token_list;
	t_tokens *token;

	token_list = mini->token;
	token = (t_tokens *) token_list->content;

	// Si el primer token es BUILTIN y el segundo es un WORD
	int condicion1 = token->type_token == BUILTINS;
	int condicion2 = token_list->next != NULL;
	int condicion3 = ((t_tokens *) (token_list->next->content))->type_token == WORD;
	if (condicion1 && condicion2 && condicion3)
	{
		while (token_list->next != NULL)
		{
			// Avanzar al primer token de tipo WORD
			token = (t_tokens *)token_list->next->content;
			if (token->type_token == WORD)
				handle_tokens((t_tokens *) token);
			else
			{
				break ;
			}
			token_list = token_list->next; // Avanzar al siguiente token
		}
	}
}

void	handle_tokens(t_tokens *token)
{
	if (handle_single_quote(token) == 1)	// echo '$hello' ->printf($hello)
	{
		printf("printf without single quotes\n");
	}
	else if (handle_special_quotes(token) == 1)	// echo " '$USER' "
	{
		if (ft_strchr_true(token->str, 36) == 1)
			handle_dollar_cases(token);
	}
	else if (handle_double_quotes(token) == 1)	// echo "$USER"
	{
		if (ft_strchr_true(token->str, 36) == 1)
			handle_dollar_cases(token);
	}

	else
	{
//		echo $hello
		if (ft_strchr_true(token->str, 36) == 1)
			handle_dollar_cases(token);
	}
}
/*
	if (token->str[0] == '\"' && token->str[token->length - 1] == '\"' &&  (ft_strchr_true(token->str, 36) == 1))
	{
		handle_dollar_cases(token); //1caso
	}
	else
		printf("entro en else");
	else if (token->str[0] == '\'' && token->str[token->length - 1] == '\'')
	{
		printf("print token->str without simple quotes\n");
	}
	else
	{
		handle_special_quotes(token);
	}	//queremos detectar si hay una simple quote '$VAR' no expande
*/


//token = (t_tokens *)current->content;  // Accede a `t_tokens` dentro de `content`
//	if (token->type_token == BUILTINS && token_list->next && ((t_tokens *)(token_list->next->content))->type_token == WORD) // echo
