/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/24 15:59:09 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"



/**
  *Objetivo: i
  * char	*get_var_value(char *line)
  * char	*get_var_name(char *line)
  * remov e quote....()
  * get_var_from_token
  * find_value_in_env
  * replace_var_in_token
 */

void	update_token_str(t_tokens *token, char **split_word)
{
	char	*new_str;

	new_str = ft_strjoin_array(split_word);
	if (new_str == NULL)
		return ;
	printf("new_str after strjoin: [%s]\n", new_str);

	free(token->str);
	token->str = ft_strdup(new_str);
	free(new_str);
}

char	*extract_var_name(const char *str)
{
	int		i;
	int		k;
	int 	start;
	char	*var_name;

	i = 0;
	start = 0;

	while ( str[i] && str[i] == SPACE)
		i ++;
	if (str[i] == DOLLAR_SIGN)
		start = i + 1;
		// posible nuevea implementacion dollar
	while (str[i] != '\0' && str[i] != SPACE)
		i ++;

	var_name = malloc(sizeof(char) * (i - start + 1));
	if (!var_name)
		return (NULL);
	k = 0;
	while (start < i)
	{
		var_name[k] = str[start];
		start ++;
		k ++;
	}
	var_name[k] = '\0';
	return (var_name);
}

char	*get_and_reconstruct_token(const char *split_word, const char *var_value)
{
	int		i;
	int		before_spaces;
	int		after_spaces;
	int		len_var_value;
	int		len_token;
	char	*update_token;
	int		j;

	// count spaces before text
	i = 0;
	before_spaces = 0;
	after_spaces = 0;
	while (split_word[i] && split_word[i] == SPACE)
	{
		before_spaces ++;
		i ++;
	}
	//	Avanzar sobre el contenido no vacío
	while (split_word[i] && split_word[i] != SPACE)
		i++;

	// count spaces after text
	while (split_word[i] && split_word[i] == SPACE)
	{
		i ++;
		after_spaces ++;
	}

	// Calculate the length of the variable value token
	len_var_value = (int) ft_strlen(var_value);
	len_token = before_spaces + len_var_value + after_spaces;

	update_token = malloc(sizeof(char) * (len_token + 1));
	if (!update_token)
		return (NULL);

	i = 0;
	j = 0;

	while (j < before_spaces)
	{
		update_token[i ++] = SPACE;
		j ++;
	}

	j = 0;
	while (j < len_var_value)
	{
		update_token[i++] = var_value[j++];
	}

	j = 0;
	while (j < after_spaces)
	{
		update_token[i++] = SPACE;
		j++;
	}
	update_token[i] = '\0';
	return (update_token);
}


void	process_split_words(char **split_word, t_list *env_list)
{
	char	*var_value;
	char	*new_value;
	char	*clean_var_name;
	int		i;

	i = 0;
	while (split_word[i] != NULL)
	{
		printf("split_word[%d]: [%s]\n", i, split_word[i]);

		// Verificar si contiene un '$'
		if (ft_strchr(split_word[i], DOLLAR_SIGN))
		{
			// Extraer el nombre de la variable desde el '$'
			clean_var_name = extract_var_name(split_word[i]);
			if (clean_var_name == NULL)
			{
				i++;
				continue;
			}
			printf("clean_var-name: [%s]\n", clean_var_name);

			// Buscar el valor en las variables de entorno
			var_value = find_value_in_env(env_list, clean_var_name);
			printf("var_value ===>: [%s]\n", var_value);

			// Reconstruir el token con el valor de la variable
			if (var_value != NULL)
				new_value = get_and_reconstruct_token(split_word[i], var_value);
			else
				new_value = get_and_reconstruct_token(split_word[i], "");

			if (new_value != NULL)
			{
				free(split_word[i]);
				split_word[i] = ft_strdup(new_value);
				free(new_value);
			}
			free(clean_var_name);
		}
		i++;
	}
}

char	**ft_split_new_version(char *str)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int wc = 0;

//	contar palabras
	while (str[i] != '\0')
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i ++;
		if (str[i])
			wc ++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i ++;
		/*
		//	cada que encuentra un signo de dolar cuenta una palabra
		if (str[i] == DOLLAR_SIGN)
			i ++;
		*/
	}
	printf("wc: [%d]\n", wc);

	char **out = (char **) malloc(sizeof(char *) * (wc + 1));
	i = 0;

	while (str[i] != '\0')
	{
		// int start_word = 0;
		// int end_word = 0;
		j = i;
		while (str[i] && (str[i] == ' '))
		{
			i ++;
		}
		// start_word = i;
		while (str[i] != '\0' && str[i] != ' ')
		{
			i ++;
		}
		// end_word = i;
		while (str[i] && (str[i] == ' ') && str[i] != '\0')
		{
			i ++;
		}

		if (i > j)
		{

			out[k] = (char *)malloc(sizeof(char) * ((i) + 1));
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}


/**
 * EXTRAEEER!!! NAME DEPSUES DEL DOLLAR
 * echo "$hello"   hello
 * echo "$USER hello world $SHLVL"
 * Nota: el caso "echo "$HOLA $USER" esta "mal"
 * porque agrega un espacio de mas al inicio.
*/

//	original

void	get_var_from_token(t_tokens *token_list, t_list *env_list)
{
	t_tokens	*curr_token;
	char		**split_word;
	int 		position_dollar;
	int			i;

	curr_token = token_list;
	while (curr_token != NULL)
	{
		if (curr_token->type_token == WORD)
		{
			// Verificar si el token contiene '$' y no está seguido de un espacio
			position_dollar = ft_strchr_c(curr_token->str, DOLLAR_SIGN);
			if (position_dollar == -1 && \
			(position_dollar + 1 < (int)ft_strlen(curr_token->str)) && curr_token->str[position_dollar + 1] == SPACE)
			{
				break ;
			}

			//TODO: add new case here :
			split_word = ft_split_new_version(curr_token->str);

			i = 0;

			while (split_word[i] != NULL)
			{
				printf("split_word[%d]: [%s]\n", i, split_word[i]);
				i ++;
			}

			if (split_word != NULL)
			{
				// Expandir variables dentro de los fragmentos divididos
				process_split_words(split_word, env_list);
				i = 0;

/*
				printf("-------------------------\n");
				while (split_word[i] != NULL)
				{
					printf("split_word[%d]: [%s]\n", i, split_word[i]);
					i ++;
				}
				printf("-------------------------\n");
*/

				// Actualizar el contenido del token con los resultados procesados
				update_token_str(curr_token, split_word);

				// Liberar memoria usada por la división del token
				free_split_result(split_word);
			}
		}
		curr_token = curr_token->next;
	}
}

/**
 *
 * @example: echo "$USER$HOME"	->	daruuu/home/daruuu
 * @example: echo "$USER$_abc this_is_a_test"	->	daruuu this_is_a_test
 * @param str
 * @return
 */

int	has_more_than_one_dollar_without_spaces_in_token(const char *str)
{
	int	i;
	int	count_dollar;

	i = 0;
	count_dollar = 0;
	while (str[i] != '\0')
	{

		if (str[i] == DOLLAR_SIGN)
		{
			count_dollar ++;
			if (str[i + 1] == DOLLAR_SIGN)
			{
				return (FALSE);
			}
		}
		i ++;
	}
	if (count_dollar > 1)
		return (TRUE);
	return (FALSE);
}

	/*
	if (has_string_before_dollar(token->str))
		return (handle_str_trim_before_dollar(token));
	*/
	/**
	 * Performs general dollar variable expansion.
	 * Key points:
	 * - Expands all dollar variables in the token using the environment list.
	 * - This is the fallback case when no special conditions are met.
	 *
	 * @example
	 * Input: `"$HOME/$USER"`.
	 * Output: `"/home/daruu/daruu"`
	*/

void	expand_dollar(t_tokens *token_list, t_list *env_list)
{
	t_tokens	*curr_token;
	char		*update_token_str;

	curr_token = token_list;
	update_token_str = NULL;
	printf("curr_token->str: [%s]\n", curr_token->str);

	while (curr_token != NULL)
	{
		update_token_str = remove_quotes_str(curr_token->str, D_QUOTE);
		printf("remove quotes: [%s]\n", update_token_str);
		curr_token->str = ft_strdup(update_token_str);
//		verificar si dollar + 1 != space
		get_var_from_token(token_list, env_list);
		curr_token = curr_token->next;
	}
}

void	copy_word_to_token(const char *word, char *merged_token, size_t *k)
{
	size_t	i;

	i = 0;
	while (word[i] != '\0')
	{
		merged_token[*k] = word[i];
		(*k) ++;
		i ++;
	}
}