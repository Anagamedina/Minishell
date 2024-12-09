#include "../../includes/minishell.h"

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
}
/************ MAIN FUNCTION *************/


void expand_dollar(t_tokens *token_list, t_env *env_list)
{

	if (validate_dollar(token_list) == 1)


}
