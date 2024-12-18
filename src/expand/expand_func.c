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

void	process_split_words(char **split_word, t_list *env_list)
{
	int	i;

	i = 0;
	while (split_word[i] != NULL)
	{
		replace_dollar_variable(&split_word[i], env_list);
		i ++;
	}
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

	curr_token = token_list;
	while (curr_token != NULL)
	{
		if (curr_token->type_token == WORD)
		{
			split_word = ft_split_quote(curr_token->str);
			if (split_word != NULL)
			{
				process_split_words(split_word, env_list);
				update_token_str(curr_token, split_word);
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
		i++;
	}
}
