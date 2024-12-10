#include "../../includes/minishell.h"

int	found_dollar_syntax(char *str);

/**
  *Objetivo: i
  * char	*get_var_value(char *line)
  * char	*get_var_name(char *line)
  remov e quote....()
  * get_var_from_token
  * find_env_value
  * replace_var_in_token
*/

// echo "$hello"   hello
char	*get_var_from_token(t_tokens *token_list)
{
	t_tokens	*curr_token;

	curr_token = token_list;
	while (curr_token != NULL)
	{
		// Verifica si el token tiene un $
		if (found_dollar_syntax(curr_token->str) == 1) {
			//si te encuentras un dolar me saltas el $ y strdup de VAR
			return (ft_strdup(curr_token->str + 1));
		}
		curr_token = curr_token->next;
	}
	return (NULL);
}


/*
char	*find_env_value(t_env *env_list, char *var_name_token)
{
	t_env	*curr_env;

	curr_env = env_list;
	while (env_list !=  NULL)
	{
		if (ft_strcmp(var_name_token, curr_env->key) == 0)
		{
			return (ft_strdup(curr_env->value));
		}
		env_list = env_list->next;
	}
	return (NULL);
}
*/

char	*find_env_value(t_list *env_list, char *var_name_token)
{
	t_list	*curr_env_list;
	t_env	*curr_env;

	// Validación inicial
	if (!env_list || !var_name_token)
		return (NULL);

	curr_env_list = env_list;
	while (curr_env_list != NULL)
	{
		// Asegurarse de que key no sea NULL antes de comparar
		curr_env = (t_env *)curr_env_list->content;
		if (curr_env->key && ft_strcmp(var_name_token, curr_env->key) == 0)
		{
			// Duplicar el valor encontrado
			return (curr_env->value ? ft_strdup(curr_env->value) : ft_strdup(""));
		}
		curr_env_list = curr_env_list->next; // Iterar con curr_env
	}
	return (NULL); // Variable no encontrada
}


/*
function auxiliar que verifique sintaxis de VAR
		$[a-zA-Z][a-zA-Z0-9]*
		$[a-zA-Z][a-zA-Z0-9]*
 gestionar que el $ siempre al principio del str
 echo $_ a-zA-Z
*/
static int	syntax_var_dollar(char *str)
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

/**
 * expand $ en Bash se refiere a la expansión de variables,
 * syntaxis: despues de $
 * 1)reemplaza el símbolo $ con el valor actual de una variable
 * 2)si la variable esté definida en el entorno del shell, buscar el valor de la variable en t_list_env
 * 3)
 * */


/************ MAIN FUNCTION *************/
//	echo $hello

void	expand_dollar(t_tokens *token_list, t_list *env_list)
{
	// Nota: Posible cambio a t_list.
    t_tokens	*curr_token;
    char		*var_name;
    char		*var_value;

	printf("entra en expand_dolar\n");
    curr_token = token_list;
    while (curr_token != NULL)
	{
        if (found_dollar_syntax(curr_token->str))	//poshile error con "$hello"
		{
            // Obtener el nombre de la variable
            var_name = get_var_from_token(curr_token);
            if (var_name)
			{
                var_value = find_env_value(env_list, var_name);
                if (var_value)
				{
                    free(curr_token->str);
                    curr_token->str = ft_strdup(var_value); // Ya es strdup desde find_env_value
                }
                free(var_name);
            }
        }
        curr_token = curr_token->next;
    }
}
