//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"

void handle_single_quote(t_tokens *token);

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
			if (token->type_token != WORD)
				break ;
			if (token->str && ft_strchr_true(token->str, 36) == 1) // Si contiene '$'
				handle_variable_expansion(token); //1caso
			else if (token->str) // si te ecnuentras una doble comilla y una simple ("''")
				handle_special_quotes(token);
			else if (token->str)
				handle_special_doble_quotes(token);//2caso cuando solo hsy comilla doble ("")
			else if (token->str)
				handle_single_quote(token);		//queremos detectar si hay una simple quote '$VAR' no expande
			token_list = token_list->next; // Avanzar al siguiente token
		}
	}
}

//token = (t_tokens *)current->content;  // Accede a `t_tokens` dentro de `content`
//	if (token->type_token == BUILTINS && token_list->next && ((t_tokens *)(token_list->next->content))->type_token == WORD) // echo
