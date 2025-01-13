/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/13 11:49:54by  dasalaza        ###   ########.fr       */
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
	free(token->str);
	if (token->str != NULL)
		token->str = ft_strdup(new_str);
	free(new_str);
}

char	*extract_var_name(char *str)
{
	int		i;
	int 	start;
	char	*var_name;

	i = 0;
	start = 0;

	while ( str[i] && str[i] == SPACE)
	{
		i ++;
	}
	if (str[i] == DOLLAR_SIGN)
	{
		start = i;
	}
	while (str[i] != '\0' && str[i] != SPACE)
	{
		i ++;
	}
	var_name = ft_substr(str, start, i);
	return (var_name);
}
char	*get_and_reconstruct_token(char *split_word, char *var_value)
{
	int		i;
	int 	end;
	char	*update_token;
	int		before_spaces;	
	int		after_spaces;

	i = 0;
	end = 0;
	before_spaces = 0;
	after_spaces = 0;
	update_token = NULL;

	while (split_word[i] && split_word[i] == SPACE)
		i ++;
	before_spaces = i;
	while (split_word[i] != '\0' && split_word[i] != SPACE)
	{
		i ++;
	}
	after_spaces = i;
	while (split_word[i] != '\0' && split_word[i] == SPACE)
		i ++;
	end = i;
	int len_var_value = ft_strlen(var_value);

	int len_token = before_spaces + len_var_value + (end - after_spaces);

	update_token = malloc(sizeof(char) * (len_token + 1));
	if (update_token == NULL)
		return (NULL);

	i = 0;
	while (i < len_token)
	{
		if (i < before_spaces)
		{
			update_token[i] = SPACE;
		}
		else if (i < (before_spaces + len_var_value))
		{
			update_token[i] = var_value[i - before_spaces];
		}
		else
		{
			update_token[i] = split_word[i - len_var_value];
		}
		i ++;
	}
	update_token[i] = '\0';
	return (update_token);
}

void	process_split_words(char **split_word, t_list *env_list)
{
	// int	i;

	// i = 0;
	// while (split_word[i] != NULL)
	// {
	// 	replace_dollar_variable(&split_word[i], env_list);
	// 	i ++;
	// }

	char	*var_value;
	int		i;

	
	i = 0;
	while ((*split_word)[i] != '\0')
	{
		printf("split_word[%d]: [%c]\n", i, (*split_word)[i]);
		if ((*split_word)[i] == DOLLAR_SIGN)
		{
			// add new function here

			char	*clean_var_name = extract_var_name(*split_word + i + 1);
			printf("clean_var-name: [%s]\n", clean_var_name);


			var_value = NULL;
			var_value = find_value_in_env(env_list, clean_var_name);
			printf("var_value: [%s]\n", var_value);

			// free(*split_word);
			// TODO: reconstruir el split_word con espacios  
			if (var_value != NULL)
			{
				// *split_word = ft_strdup(var_value);
				*split_word = get_and_reconstruct_token(*split_word[i], var_value);
				printf("split_word: [%s]\n", *split_word);
			}
			else
			{
				*split_word = ft_strdup("");
			}
		}
		else
		{
			i ++;
			printf("i: [%d]\n", i);
		}
	}
}

char	**ft_split_new_version(char *str)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int wc = 0;

//	contar palabras
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
	}

	char **out = (char **) malloc(sizeof(char *) * (wc + 1));
	i = 0;

	while (str[i] != '\0')
	{
		int start_word = 0;
		int end_word = 0;
		int spaces_before_start = 0;
		int spaces_end = 0;
		j = i;
		while (str[i] && (str[i] == ' '))
		{
			spaces_before_start ++;
			i ++;
		}
		start_word = i;
		while (str[i] != '\0' && str[i] != ' ')
		{
			i ++;
		}
		end_word = i;
		while (str[i] && (str[i] == ' ') && str[i] != '\0')
		{
			spaces_end ++;
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

void	get_var_from_token(t_tokens *token_list, t_list *env_list)
{
	t_tokens	*curr_token;
	char		**split_word;
	int 		position_dollar;

	curr_token = token_list;
	while (curr_token != NULL)
	{
		if (curr_token->type_token == WORD)
		{
			// Verificar si el token contiene '$' y no está seguido de un espacio
			position_dollar = ft_strchr_c(curr_token->str, DOLLAR_SIGN);
			if (position_dollar != -1 && \
			(position_dollar + 1 < (int)ft_strlen(curr_token->str)) && \
				curr_token->str[position_dollar + 1] == SPACE)
			{
				break ;
			}

			//TODO: add new case here :
			split_word = ft_split_new_version(curr_token->str);

			int i = 0;

			while (split_word[i] != NULL)
			{
				printf("split_word[%d]: [%s]\n", i, split_word[i]);
				i ++;
			}
			

			if (split_word != NULL)
			{
				// Expandir variables dentro de los fragmentos divididos
				process_split_words(split_word, env_list);

				// Actualizar el contenido del token con los resultados procesados
				update_token_str(curr_token, split_word);

				// Liberar memoria usada por la división del token
				free_split_result(split_word);
			}
		}
		curr_token = curr_token->next;
	}
}

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
		printf("removequotes: [%s]\n", update_token_str);
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
		(*k)++;
		i++;
	}
}

