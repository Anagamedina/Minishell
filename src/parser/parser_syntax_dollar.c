//
// Created by daruuu on 12/1/24.
//
#include "../../includes/minishell.h"


char	*remove_quotes_str(char *str, char c)
{
	int		i;
	int		j;
	int		new_len;
	char	*new_str;

	i = 0;
	new_len = 0;
	// Calcula la longitud del nuevo string sin el carácter c
	while (str[i] != '\0')
	{
		if (str[i] != c)
			new_len++;
		i++;
	}
	new_str = (char *)malloc(sizeof(char) * (new_len + 1));
	if (new_str == NULL)
		return (NULL);
	// Reconstruye el nuevo string sin el carácter c
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(str); // Libera el string original
	return (new_str);
}

/**
 * this function
 * check if a WORD contains a $ and expand it
 *
*/
void	parser_tokens(t_mini *mini)
{
	t_list	*token_list;
	t_list	*env_list;

	t_tokens *token;
	t_env	*env_var;

	token_list = mini->token;
	env_list = mini->env;


	token = (t_tokens *) token_list->content;
	env_var = (t_env *)env_list->content;

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
				handle_tokens((t_tokens *) token, env_var);
			else
				break ;
			token_list = token_list->next; // Avanzar al siguiente token
		}
	}
}

void handle_tokens(t_tokens *token, t_env *env_list)
{
	char	*result;

	if (handle_single_quote(token) == 1)	// echo '$hello' ->printf($hello)
	{
		printf("printf without single quotes\n");
		result = remove_quotes_str(token->str, '\'');
		printf("%s\n", result);
		expand_dollar(token, env_list);
	}
	else if (handle_special_quotes(token) == 1)	// echo " '$USER' "
	{
		if (ft_strchr_true(token->str, 36) == 1)
			handle_dollar_cases(token, env_list);
	}
	else if (handle_double_quotes(token) == 1)	// echo "$USER"
	{
		if (ft_strchr_true(token->str, 36) == 1)
			handle_dollar_cases(token, env_list);
	}
	else
	{
//		echo $hello
		if (ft_strchr_true(token->str, 36) == 1)
			handle_dollar_cases(token, env_list);
	}
}
