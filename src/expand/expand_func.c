#include "../../includes/minishell.h"


/**
  *Objetivo: i
  * char	*get_var_value(char *line)
  * char	*get_var_name(char *line)
  remov e quote....()
  * get_var_from_token
  * find_env_value
  * replace_var_in_token
*/
char	*ft_strjoin_array(char **split_word);

//EXTRAEEER!!! NAME DEPSUES DEL DOLLAR
// echo "$hello"   hello
//echo "$USER hello world $SHLVL"
//	TODO: finish this function
// Nota: el caso "echo "$HOLA $USER" esta "mal" porque agrega un espacio de mas al inicio.
char	*get_var_from_token(t_tokens *token_list, t_list *env_list)
{
	t_tokens	*curr_token;
	char 		**split_word;
	int 		i;
	char 		*var_name;
	char 		*var_value;
	char 		*tmp_new_token_str;

	curr_token = token_list;
	while (curr_token != NULL)
	{
		if (curr_token->type_token == WORD)
		{
			split_word = ft_split_quote(curr_token->str);
			i = 0;
			if (split_word != NULL)
			{
				while (split_word[i] != NULL)
				{
					if (split_word[i][0] == DOLLAR_SIGN) // si el primer caracter es un $
					{
						var_name = ft_strdup(split_word[i] + 1);
						var_value = find_env_value(env_list, var_name);
						printf("var_value: %s\n", var_value);
						if (var_value != NULL)
						{
							free(split_word[i]);
							split_word[i] = ft_strdup(var_value);
						}
						else // si no se encuentra el valor de la variable se deja vacio
						{
							free(split_word[i]);
							split_word[i] = ft_strdup(" ");
						}
						free(var_name);
						free(var_value);
					}
					i++;
				}
			}
			tmp_new_token_str = ft_strjoin_array(split_word);
			if (curr_token->str != NULL)
			{
				free(curr_token->str);
			}
			curr_token->str = ft_strdup(tmp_new_token_str);
			if (tmp_new_token_str != NULL)
			{
				free(tmp_new_token_str);
			}
		}
		curr_token = curr_token->next;
	}
	return (tmp_new_token_str);
}

char	*ft_strncpy(char *dst, const char *src,  int n)
{
	int i = 0;
	while(i < n && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin_array(char **split_word)
{
	int		i;
	int		j;
	int 	k;
	char	*merged_token;
	size_t	new_len;

	i = 0;
	new_len = 0;
	while (split_word[i] != NULL)
	{
		new_len += ft_strlen(split_word[i]);
		new_len++;
		i++;
	}
	new_len --;
	merged_token = (char *)malloc(sizeof(char) * (new_len + 1));
	if (merged_token == NULL)
		return (NULL);

	i = 0;
	int word_len = 0;
	k = 0;
	while (split_word[i] != NULL)
	{
		word_len = ft_strlen(split_word[i]);
		j = 0;
		while (split_word[i][j] != '\0')
		{
			merged_token[k] = split_word[i][j];
			if (word_len - 1 == j)
			{
				k++;
				merged_token[k] = ' ';
			}
			j++;
			k++;
		}

		i ++;
	}
	merged_token[new_len] = '\0';
	return (merged_token);
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
	while (str[i] != '\0')
	{
		if (str[i] == DOLLAR_SIGN)
		{
			if (syntax_var_dollar(&str[i + 1]))
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
	char		*update_token_str;

    curr_token = token_list;
    while (curr_token != NULL)
	{
		update_token_str = remove_quotes_str(curr_token->str, D_QUOTE);
		printf("update_token: %s\n", update_token_str);
		curr_token->str = ft_strdup(update_token_str);
		printf("curr->token : %s\n", curr_token->str);
		char *tmp = get_var_from_token(token_list, env_list);
		printf("tmp: %s\n", tmp);
        curr_token = curr_token->next;
    }
}
