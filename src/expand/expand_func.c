/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/17 17:55:47 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
  *Objetivo: i
  * char	*get_var_value(char *line)
  * char	*get_var_name(char *line)
  * remov e quote....()
  * get_var_from_token
  * find_env_value
  * replace_var_in_token
 */
char	*ft_strjoin_array(char **split_word);

/**
 * EXTRAEEER!!! NAME DEPSUES DEL DOLLAR
 * echo "$hello"   hello
 * echo "$USER hello world $SHLVL"
 * Nota: el caso "echo "$HOLA $USER" esta "mal"
 * porque agrega un espacio de mas al inicio.
*/

char	*get_var_from_token(t_tokens *token_list, t_list *env_list)
{
	t_tokens	*curr_token;
	char		**split_word;
	int			i;
	char		*tmp_new_token_str;

	curr_token = token_list;
	while (curr_token != NULL)
	{
		if (curr_token->str == WORD)
		{
			split_word = ft_split_quote(curr_token->str);
			i = 0;
			if (split_word != NULL)
			{
				while (split_word[i] != NULL)
					split_words_aux(split_word[i++], env_list);
			}
			tmp_new_token_str = ft_strjoin_array(split_word);
			if (curr_token->str != NULL)
				free(curr_token->str);
			curr_token->str = ft_strdup(tmp_new_token_str);
			if (tmp_new_token_str != NULL)
				free(tmp_new_token_str);
		}
		curr_token = curr_token->next;
	}
	return (tmp_new_token_str);
}

/*
char	*get_var_from_token(t_tokens *token_list, t_list *env_list)
{
	t_tokens	*curr_token;
	char		**split_word;
	int			i;
	char		*var_name;
	char		*var_value;
	char		*tmp_new_token_str;

	curr_token = token_list;
	while (curr_token != NULL)
	{
		if (curr_token->type_token == WORD)
		{
			split_word = ft_split_quote(curr_token->str);
			split_words_aux(split_word);
			i = 0;
			if (split_word != NULL)
			{
				while (split_word[i] != NULL)
				{
					if (split_word[i][0] == DOLLAR_SIGN)
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
*/

static char	*get_size_split_and_malloc(char **split_word)
{
	size_t	new_len;
	int		i;
	char	*merged_token;

	new_len = 0;
	i = 0;
	while (split_word[i] != NULL)
	{
		new_len += ft_strlen(split_word[i]);
		new_len++;
		i++;
	}
	merged_token = NULL;
	merged_token = (char *)malloc(sizeof(char) * (i + 1));
	if (merged_token == NULL)
		return (NULL);
	merged_token[i] = '\0';
	return (merged_token);
}

char	*ft_strjoin_array(char **split_word)
{
	int		i;
	int		j;
	int		k;
	char	*merged_token;
	size_t	word_len;

	merged_token = get_size_split_and_malloc(split_word);
	i = 0;
	k = 0;
	while (split_word[i] != NULL)
	{
		word_len = ft_strlen(split_word[i]);
		j = 0;
		while (split_word[i][j] != '\0')
		{
			merged_token[k] = split_word[i][j];
			if ((int)(word_len - 1) == j)
			{
				k++;
				merged_token[k] = ' ';
			}
			j++;
			k++;
		}
		i ++;
	}
	return (merged_token);
}


char	*find_env_value(t_list *env_list, char *var_name_token)
{
	t_list	*curr_env_list;
	t_env	*curr_env;

	if (!env_list || !var_name_token)
		return (NULL);

	curr_env_list = env_list;
	while (curr_env_list != NULL)
	{
		curr_env = (t_env *)curr_env_list->content;
		if (curr_env->key && (ft_strcmp(var_name_token, curr_env->key) == 0))
		{
			if (curr_env->value != NULL)
				return (ft_strdup(curr_env->value));
			else
				return (ft_strdup(""));
		}
		curr_env_list = curr_env_list->next;
	}
	return (NULL);
}


/*
function auxiliar que verifique sintaxis de VAR
		$[a-zA-Z][a-zA-Z0-9]*
		$[a-zA-Z][a-zA-Z0-9]*
 gestionar que el $ siempre al principio del str
 echo $_ a-zA-Z
*/
/*
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
*/

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
	t_tokens	*curr_token;
	char		*update_token_str;
	char		*tmp;

	curr_token = token_list;
	update_token_str = NULL;
	while (curr_token != NULL)
	{
		update_token_str = remove_quotes_str(curr_token->str, D_QUOTE);
		curr_token->str = ft_strdup(update_token_str);
		printf("curr_token->str: %s\n", curr_token->str);
		tmp = ft_strdup(get_var_from_token(token_list, env_list));
		printf("get_var_from_token(): %s\n", tmp);
		curr_token = curr_token->next;
	}
}
