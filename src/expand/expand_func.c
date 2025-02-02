/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/02 23:10:18 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_token_str(t_tokens *token, char **split_word)
{
	char	*new_str;

	new_str = ft_strjoin_array(split_word);
	if (new_str == NULL)
		return ;
	free(token->str);
	token->str = new_str;
}

char	*extract_var_name(const char *str)
{
	int		i;
	int		start;
	char	*var_name;

	i = 0;
	start = 0;
	while (str[i] && str[i] == SPACE)
		i ++;
	if (str[i] == DOLLAR_SIGN)
		start = i + 1;
	while (str[i] != '\0' && str[i] != SPACE)
		i ++;
	var_name = malloc(sizeof(char) * (i - start + 1));
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, &str[start], i - start);
	var_name[i - start] = '\0';
	return (var_name);
}

char	*get_and_reconstruct_token(char *split_word, const char *var_val, int i)
{
	int		before;
	int		after;
	int		len_token;
	char	*new_token;

	before = 0;
	while (split_word[i] && split_word[i] == SPACE)
		before ++;
	while (split_word[i] && split_word[i] != SPACE)
		i ++;
	after = 0;
	while (split_word[i] && split_word[i] == SPACE)
		after ++;
	len_token = before + (int) ft_strlen(var_val) + after;
	new_token = malloc(sizeof(char) * (len_token + 1));
	if (!new_token)
		return (NULL);
	ft_memset(new_token, SPACE, before);
	ft_memcpy(new_token + before, var_val, ft_strlen(var_val));
	ft_memset(new_token + before + ft_strlen(var_val), SPACE, after);
	new_token[len_token] = '\0';
	return (new_token);
}

void	replace_env_var_in_token(char **token, t_list *env_list)
{
	char	*var_name;
	char	*var_value;
	char	*new_token;

	var_name = extract_var_name(*token);
	if (!var_name)
		return ;
	var_value = find_value_in_env(env_list, var_name);
	free(var_name);
	new_token = get_and_reconstruct_token(*token, var_value, 0);
	if (!new_token)
		return ;
	free(*token);
	*token = ft_strdup(new_token);
	free(new_token);
}

void	process_split_words(char **split_word, t_list *env_list)
{
	int		i;

	i = 0;
	while (split_word[i])
	{
		if (!ft_strchr(split_word[i], DOLLAR_SIGN))
		{
			i++;
			continue ;
		}
		replace_env_var_in_token(&split_word[i], env_list);
		i++;
	}
}

/*
 *ORIGINAL
void	process_split_words(char **split_word, t_list *env_list)
{
	int		i;
	char	*var_value;
	char	*new_token;
	char	*clean_var_name;

	i = 0;
	while (split_word[i] != NULL)
	{
		if (!ft_strchr(split_word[i], DOLLAR_SIGN))
		{
			i ++;
			continue ;
		}
		clean_var_name = extract_var_name(split_word[i]);
		if (clean_var_name == NULL)
			return ;
		var_value = find_value_in_env(env_list, clean_var_name);
		free(clean_var_name);
		new_token = get_and_reconstruct_token(split_word[i], var_value, 0);
		if (new_token)
		{
			free(split_word[i]);
			split_word[i] = ft_strdup(new_token);
			free(new_token);
		}
		i ++;
	}
}
*/

static int	count_words(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i] != '\0')
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i++;
	}
	return (wc);
}

static char	**allocate_output_array(int wc)
{
	return ((char **)malloc(sizeof(char *) * (wc + 1)));
}

static void	free_output_array(char **out, int words_allocated)
{
	int	i;

	i = 0;
	while (i < words_allocated)
		free(out[i++]);
	free(out);
}

static void	fill_output_array(char *str, char **out)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		j = i;
		while (str[i] && (str[i] == ' '))
			i++;
		while (str[i] != '\0' && str[i] != ' ')
			i++;
		while (str[i] && (str[i] == ' ') && str[i] != '\0')
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			if (!out[k])
			{
				free_output_array(out, k);
				return ;
			}
			ft_strncpy(out[k++], &str[j], i - j);
			out[k][i - j] = '\0';
		}
	}
	out[k] = NULL;
}

char	**ft_split_new_version(char *str)
{
	int		wc;
	char	**out;

	wc = count_words(str);
	out = allocate_output_array(wc);
	if (!out)
		return (NULL);
	fill_output_array(str, out);
	return (out);
}

/*
 *ORIGINAL
char	**ft_split_new_version(char *str)
{
	int		i;
	int		j;
	int		k;
	int		wc;
	char	**out;

	i = 0;
	j = 0;
	k = 0;
	wc = 0;
	while (str[i] != '\0')
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i ++;
		if (str[i])
			wc ++;
		while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
			i ++;
	}
	out = (char **) malloc(sizeof(char *) * (wc + 1));
	i = 0;
	while (str[i] != '\0')
	{
		j = i;
		while (str[i] && (str[i] == ' '))
			i ++;
		while (str[i] != '\0' && str[i] != ' ')
			i ++;
		while (str[i] && (str[i] == ' ') && str[i] != '\0')
			i ++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i) + 1));
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}
*/

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
	int			position_dollar;

	curr_token = token_list;
	while (curr_token != NULL)
	{
		if (curr_token->type_token == WORD)
		{
			position_dollar = ft_strchr_c(curr_token->str, DOLLAR_SIGN);
			if (position_dollar == -1 \
				&& (position_dollar + 1 < (int)ft_strlen(curr_token->str)) \
				&& curr_token->str[position_dollar + 1] == SPACE)
				break ;
			split_word = ft_split_new_version(curr_token->str);
			if (split_word != NULL)
			{
				process_split_words(split_word, env_list);
				update_token_str(curr_token, split_word);
				free_string_array(split_word);
			}
		}
		curr_token = curr_token->next;
	}
}

/**
 * @example: echo "$USER$HOME"	->	daruuu/home/daruuu
 * @example: echo "$USER$_abc this_is_a_test"	->	daruuu this_is_a_test
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
				return (FALSE);
		}
		i ++;
	}
	if (count_dollar > 1)
		return (TRUE);
	return (FALSE);
}

void	expand_dollar(t_tokens *token_list, t_list *env_list)
{
	t_tokens	*curr_token;
	char		*update_token_str;

	curr_token = token_list;
	update_token_str = NULL;
	while (curr_token != NULL)
	{
		update_token_str = remove_quotes_str(curr_token->str, D_QUOTE);
		curr_token->str = ft_strdup(update_token_str);
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
		i ++;
	}
}

/*
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
				new_value = get_and_reconstruct_token(split_word[i], \
				var_value, 0);
			else
				new_value = get_and_reconstruct_token(split_word[i], "", 0);
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
*/

/*
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
		i ++;
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
		j ++;
	}
	update_token[i] = '\0';
	return (update_token);
}
*/
