/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 11:42:28 by anamedin         ###   ########.fr       */
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
//????? leaks??

static void	process_split_words(char **split_word, t_list *env_list)
{
	int	i;
	char *tmp;

	i = 0;
	while (split_word[i])
	{
		if (!ft_strchr(split_word[i], DOLLAR_SIGN))
		{
			i++;
			continue ;
		}
		tmp = split_word[i];  // Guardamos el puntero original antes de modificarlo
		replace_env_var_in_token(&split_word[i], env_list);
		free(tmp);  // Liberamos la memoria anterior de split_word[i]
		i++;
	}
}

/*static void	process_split_words(char **split_word, t_list *env_list)
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
}*/

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
