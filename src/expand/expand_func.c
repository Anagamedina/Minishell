#include "../../includes/minishell.h"

char *extract_value_env(char *str, t_env *env_list);

/*
function auxiliar que verifique sintaxis de VAR
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
//iterar por cada argumento de cada TOKEN y
// le pasamos una funcion auxiliar de syntaxis
//verificar que contiene un $

int	found_dollar_syntax(char *str)
{
	int i;

	if (!str)
		return (FALSE);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] != '\0' && syntax_var_dollar(&str[i + 1]))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}


/**expand $ en Bash se refiere a la expansión de variables,
 * syntaxis: despues de $
 * 1)reemplaza el símbolo $ con el valor actual de una variable
 * 2)si la variable esté definida en el entorno del shell, buscar el valor de la variable en t_list_env
 * 3)
 *
 * */
/*
int validate_dollar(t_tokens *token_list)
{
	t_tokens	*curr_token;
	//t_env		*curr_env;

	curr_token = token_list;
	//curr_env = env_list->content;
//	verificar syntax

	while (curr_token != NULL)
	{
		if (found_dollar_syntax(curr_token->str) == 1)
		{
			return (TRUE);
		}
		curr_token = curr_token->next;
	}
	return (FALSE);
}*/

/************ MAIN FUNCTION *************/

// echo hello $USER $ana
/*
void	expand_dollar(t_tokens *token_list, t_env *env_list)
{
	t_tokens	*curr_token;

	curr_token = token_list;
	while (token_list != NULL)
	{
		if (found_dollar_syntax(curr_token->str) == 1)
		{
			token_list->str = extract_value_env(curr_token->str, (t_list *) env_list);
		}
		token_list = token_list->next;
	}
}

char	*extract_value_env(char *str, t_list *env_list)
{
	t_list	*curr_env;
	t_env	*env_var;

	curr_env = env_list;
	while (curr_env != NULL)
	{
		env_var = (t_env *)curr_env->content;
		printf("env_var->key: %s\n", env_var->key);
		if (ft_strcmp((char *)env_var->key, str + 1) == 0)
		{
			return (ft_strdup(env_var->value));
		}
		curr_env = curr_env->next;
	}
	return (NULL);
}
*/

void expand_dollar(t_tokens *token_list, t_env *env_list)
{
	t_tokens	*curr_token;
	char		*expanded_value;

	curr_token = token_list;
	expanded_value = NULL;
	while (curr_token != NULL)
	{
		// Verifica si el token tiene un $
		if (found_dollar_syntax(curr_token->str) == 1)
		{
			// Expande la variable
//			expanded_value = extract_value_env(curr_token->str, env_list);
//			expanded_value = get_var_name(curr_token->str);
			while (env_list != NULL)
			{
				if (ft_strcmp(env_list->key, curr_token->str) == 0)
				{
				}
			}







			if (expanded_value != NULL)
			{
				// Libera el valor anterior y asigna el nuevo valor expandido
				free(curr_token->str);
				curr_token->str = expanded_value;
			}
		}
		curr_token = curr_token->next;
	}
}

/*char	*extract_value_env(char *str, t_env *env_list)
{
	t_env	*curr_env;

	// Validar entrada
	if (!str || str[0] != '$' || !env_list)
		return (NULL);

	curr_env = env_list;
	while (curr_env != NULL)
	{
		// Validar que la clave no sea NULL antes de comparar
		if (curr_env->key && ft_strcmp(curr_env->key, str + 1) == 0)
		{
			return (ft_strdup(curr_env->value)); // Retornar una copia del valor
		}
		curr_env = curr_env->next;
	}
	return (NULL);
}*/
