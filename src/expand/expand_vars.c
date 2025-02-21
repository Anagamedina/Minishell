/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/21 14:20:16 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	replace_env_var_in_token(char **token, t_list *env_list)
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

static void	process_split_words(char **split_word, t_list *env_list)
{
	int	i;

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

static int	process_token(t_tokens *curr_token, t_list *env_list)
{
	char	**split_word;

	split_word = ft_split_new_version(curr_token->str);
	if (!split_word)
		return (0);
	process_split_words(split_word, env_list);
	if (!update_token_str(curr_token, split_word))
	{
		free_string_matrix(split_word);
		return (0);
	}
	free_string_matrix(split_word);
	return (1);
}

void	get_var_from_token(t_tokens *token_list, t_list *env_list)
{
	t_tokens	*curr_token;
	int			pos_dolar;

	curr_token = token_list;
	while (curr_token != NULL)
	{
		if (curr_token->type_token == WORD)
		{
			pos_dolar = ft_strchr_c(curr_token->str, DOLLAR_SIGN);
			if (pos_dolar == -1 && curr_token->str[pos_dolar + 1] == SPACE && \
				(pos_dolar + 1 < (int)ft_strlen(curr_token->str)))
				break ;
			if (!process_token(curr_token, env_list))
				return ;
		}
		curr_token = curr_token->next;
	}
}

/*
void	get_var_from_token(t_tokens *token_list, t_list *env_list)
{
	t_tokens	*curr_token;
	char		**split_word;
	int			pos_dolar;

	curr_token = token_list;
	while (curr_token != NULL)
	{
		if (curr_token->type_token == WORD)
		{
			pos_dolar = ft_strchr_c(curr_token->str, DOLLAR_SIGN);
			if (pos_dolar == -1 && curr_token->str[pos_dolar + 1] == SPACE && \
				(pos_dolar + 1 < (int)ft_strlen(curr_token->str)))
				break ;
			split_word = ft_split_new_version(curr_token->str);
			if (!split_word)
				return ;
			process_split_words(split_word, env_list);
			if (!update_token_str(curr_token, split_word))
			{
				free_string_matrix(split_word);
				return ;
			}
			free_string_matrix(split_word);
		}
		curr_token = curr_token->next;
	}
}
*/

/*
static void	expand_dollar(t_tokens *token_list, t_list *env_list)
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
*/

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
