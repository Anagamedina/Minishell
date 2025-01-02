
#include "../../includes/minishell.h"

int	check_special_c(char c)
{
	if (c == '=' || c == '@' || c == '#' || c == '-' || c == '+' || c == '{'
		|| c == '}' || c == '[' || c == ']' || c == '!' || c == '~' || c == '?'
		|| c == '%' || c == '^' || c == '=' || c == '*' || c == '/' || c == '$'
		|| c == ';' || c == ':' || c == '|' || c == '.' || c == '_' || c == ',')
		return (TRUE);
	return (FALSE);
//	|| c == ';' || c == ':' || c == '|' || c == '<' || c == '>' || c == '\\')
}

void	handle_tokens(t_tokens *token, t_list *env_list)
{
	char	*tmp;

	tmp = NULL;

	/**
	 * Case single quotes:
	 * @example
	 * Input: "\'example_token\'";
	 * Output: "example_token";
	 *
	 * Si el token está rodeado por comillas simples ('), estas se eliminan.
	 * Llamada a handle_single_quote para verificar.
	 * Uso de remove_quotes_str para eliminar las comillas simples del token.
	 */

	if (handle_single_quote(token))
	{
		tmp = remove_quotes_str(token->str, S_QUOTE);
		token->str = ft_strdup(tmp);
		free(tmp);
		return ;
	}

	/**
	 * Caso Comillas Especiales:
	 * @example
	 * Input: "\"  'test $USER' \""
	 *
	 * Output: "  'test daruuu '"
	 *
	 * Si el token está rodeado por comillas dobles (") con comillas simples (') en el interior,
	  y contiene un signo de dólar ($), se manejan los casos relacionados con variables de entorno.

	 * Call a handle_special_quotes para verificar el patrón de comillas.
	 * Si incluye un dólar ($), se llama a handle_dollar_cases.
	 */

//	echo "'$USER'"
//	echo " ' $USER ' "
	if (handle_special_quotes(token))
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
		{
			handle_dollar_cases(token, env_list);
			return ;
		}
	}
	/**
	 *
	 * Caso Comillas Dobles:
	 * @example
	 * Input: "\"$HOME/projects\""
	 * Output: "/home/daruu/projects"
	 *
	 * Si el token está rodeado únicamente por comillas dobles ("), se manejan los casos relacionados con la expansión de variables de entorno ($).
	 * Llamada a has_even_double_quotes para verificar.
	 * Se llama a handle_dollar_cases para manejar variables de entorno.

	 */

//	TODO: modificar para manejar comillas dobles par veces
//	no pudne haber dolar entre d_quotes
//	echo """        """
	if (has_even_double_quotes(token))
	{
		handle_dollar_cases(token, env_list);
		return ;
	}
}

void	parser_tokens(t_mini *mini)
{
	t_list		*token_list;
	t_list		*env_list;
	t_tokens	*curr_token;

	token_list = mini->token;
	env_list = mini->env;
	curr_token = (t_tokens *) token_list->content;

	if ((curr_token->type_token == BUILTINS) && (token_list->next != NULL) \
		&& (((t_tokens *)(token_list->next->content))->type_token == WORD))
	{
		while (token_list->next != NULL)
		{
			curr_token = (t_tokens *)token_list->next->content;
			if (curr_token->type_token == WORD)
				handle_tokens((t_tokens *) curr_token, env_list);
			else
				break ;
			token_list = token_list->next;
		}
	}
}