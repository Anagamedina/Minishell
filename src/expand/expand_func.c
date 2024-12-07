#include "../../includes/minishell.h"

/**expand $ en Bash se refiere a la expansión de variables,
 * 1)reemplaza el símbolo $ con el valor actual de una variable
 * 2)si la variable esté definida en el entorno del shell, buscar el valor de la variable en t_list_env
 * 3)
 *
 * */

void expand_func(t_list *token_list, t_list *env_list)
{
	t_tokens	*curr_token;
	t_env		*curr_env;

	curr_token = token_list->content;
	curr_env = env_list->content;
//	verificar syntax


	if (token->type == WORD && ft_strchr(token->content, '$') != NULL)
	{

	}
}