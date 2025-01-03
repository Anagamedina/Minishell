
#include "../../includes/minishell.h"

int handle_special_balanced_dquotes(t_tokens *token);

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
	 * remove comillas simples ('),
	 * verificar con handle_single_quote
	 * Utilizar remove_quotes_str para eliminar squotes.
	 *
	 * TODO: gestionar mas de una sola single quote en un string ??
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
	 *
	 * Case valid: echo "'$USER hello'"
	 * Case valid: echo " '$USER hello ' "
	 * Case valid: echo """'$USER'"""
	 *
	 * Case invalid: echo "" ' $USER ' ""
	 *
	 * gestion de comillas dobles impares(impares expanden las varibales)
	 *
	 * Si incluye un dólar ($), se llama a handle_dollar_cases.
	 */

	if (handle_special_quotes(token))
	{
		if (ft_strchr_true(token->str, DOLLAR_SIGN))
		{
			handle_dollar_cases(token, env_list);
			return ;
		}
		else
		{
			printf("entro en handle_special_quotes cuando es false y no hay $\n");
//			TODO: falta implementar el caso donde no hay $ en el string
			tmp = remove_quotes_str(token->str, D_QUOTE);
			token->str = ft_strdup(tmp);
			free(tmp);
			return ;
		}
	}

	/**
	 * doble comillas son pares :
	 * @example
	 * echo " " '$USER ' " "
	 * echo " "" " '$USER ' " "" "
	 * echo "'helo $USER 0-9'"
	 */
	if (handle_special_balanced_dquotes(token))
	{
		printf("entro en handle_special_balanced_dquotes\n");

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