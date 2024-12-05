//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"

//function auxiliar que verifique sintaxis de VAR $
//		$[a-zA-Z][a-zA-Z0-9]*
//		$[a-zA-Z][a-zA-Z0-9]*
// gestionar que el $ siempre al principio del str
// echo $_ a-zA-Z
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
 * check if the next character is a single quote like $'hello
 * echo "'$USER'"
 */
int	check_single_quote_after_dollar(const char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '\'') // Si la siguiente es una comilla simple
				return (1); // Retorna 1 si se detecta
		}
		i++;
	}
	return (0); // Retorna 0 si no encuentra el patrón `$'`
}

/**
 * check if the previous character is a backslash like \\$hello
 * return TRUE or FALSE
 * echo "\$aaa
 */
int	check_backslash_before_dollar(const char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (i > 0 && str[i - 1] == '\\') // Si la anterior es una comilla doble
				return (1); // Retorna 1 si se detecta
		}
		i++;
	}
	return (0);
}

void handle_variable_expansion(t_tokens *token)
{
	if (check_single_quote_after_dollar(token->str) == 1 &&
		check_backslash_before_dollar(token->str) == 1)
	{
		printf("single quote after $\n");
		printf("token->str: [%s]\n", token->str);
	}
	else
	{
		printf("call function to expand variable\n");
		// Aquí llamarías a la función expand_dollar o equivalente
	}
}

//"' '"
void	handle_special_quotes(t_tokens *token)
{
	if (token->str[0] == '\"' &&
		token->str[token->length - 1] == '\"' &&
		token->str[1] == '\'' &&
		token->str[token->length - 2] == '\'') // echo " '$USER' "
	{
		if (check_single_quote_after_dollar(token->str) == 1)
		{
			printf("single quote after $\n");
			printf("token->str: [%s]\n", token->str);
		}
		else
		{
			printf("call function to expand variable in handle_special_quote()\n");
		}
	}
}

void	check_syntax_dollar(t_mini *mini)
{
	t_list	*token_list;
	t_tokens *token;
//	t_tokens *token1;

	token_list = mini->token;
	token = (t_tokens *) token_list->content;
//	token1 = (t_tokens *) token_list->next->content;

	//token = (t_tokens *)current->content;  // Accede a `t_tokens` dentro de `content`
	// Si el primer token es BUILTIN y el segundo es un WORD
	int condicion1 = token->type_token == BUILTINS;
	int condicion2 = token_list->next != NULL;
	int condicion3 = ((t_tokens *) (token_list->next->content))->type_token == WORD;
	if (condicion1 && condicion2 && condicion3) // echo

//	if (token->type_token == BUILTINS && token_list->next && ((t_tokens *)(token_list->next->content))->type_token == WORD) // echo
	{
		token = (t_tokens *)token_list->next->content; // Avanzar al primer token de tipo WORD
		while (token != NULL && token->type_token == WORD)
		{
			if (ft_strchr_c(token->str, '$')) // Si contiene '$'
				handle_variable_expansion(token);
			else
				handle_special_quotes(token);
			token = token->next; // Avanzar al siguiente token
		}
	}
}
