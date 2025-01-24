/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:28:28 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/24 15:59:46 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/13 12:41:00 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_char(char *str, char c)
{
	char	*result;
	size_t	len;

	len = ft_strlen(str);
	result = NULL;
	result = malloc(sizeof(char) * (len + 2));
	if (!result)
		return (NULL);
	ft_strcpy(result, str);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}

char	*find_value_in_env(t_list *env_list, char *var_name_token)
{
	t_list	*curr_env_list;
	t_env	*curr_env;

	if (!env_list || !var_name_token)
		return (NULL);

	curr_env_list = env_list;

	printf("var_name_token: [%s]\n", var_name_token);

	while (curr_env_list != NULL)
	{
		curr_env = (t_env *)curr_env_list->content;

		if (curr_env->key && (ft_strcmp(var_name_token, curr_env->key) == 0))
		{
			if (curr_env->value != NULL)
				return (ft_strdup(curr_env->value));
			else
				return (NULL);
		}
		curr_env_list = curr_env_list->next;
	}
	return (NULL);
}

void	replace_dollar_variable(char **split_word, t_list *env_list)
{
	char	*var_name;
	char	*var_value;
	int		i;

	
	i = 0;
	while ((*split_word)[i] != '\0')
	{
		if ((*split_word)[i] == DOLLAR_SIGN)
		{
			var_name = ft_strdup(*split_word + 1);
			if (var_name == NULL)
				return ;
			var_value = find_value_in_env(env_list, var_name);

			free(*split_word);
			if (var_value != NULL)
			{
				*split_word = ft_strdup(var_value);
			}
			else
			{
				*split_word = ft_strdup("");
			}
		}
		else
		{
			i ++;
		}
	}
	free(var_name);
	free(var_value);
}

char	*replace_dollar_variable_skip_s_quote(char *token_rm_d_quote, t_list *env_list)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*tmp;
	size_t	i;

//	printf("token_rm_d_quote: [%s]\n", token_rm_d_quote);

	if (!token_rm_d_quote || !env_list)
		return (NULL);

	result = ft_strdup("");
	if (result == NULL)
		return (NULL);

	//len_str = (int) ft_strlen(token_rm_d_quote);

	i = 0;
	while (token_rm_d_quote[i] != '\0')
	{
		if (token_rm_d_quote[i] == DOLLAR_SIGN)
		{
			i ++;
			// start apunta al inico del nombre de la variable
			int start = i;
			// Bucle para calcular la longitud del nombre de la variable var name.
//			$user helllooo
			while (token_rm_d_quote[i] != '\0' && token_rm_d_quote[i] != SPACE && token_rm_d_quote[i] != S_QUOTE)
			{
				i ++;
			}
//			printf("len_var_name: %ld\n", len_var_name);
			var_name = ft_substr(token_rm_d_quote, start, i - start);
			if (var_name == NULL)
			{
				free(result);
				return (NULL);
			}

			var_value = find_value_in_env(env_list, var_name);
			free(var_name);

			tmp = result;
			result = ft_strjoin(result, var_value ? var_value : "");
			free(tmp);
		}
		else
		{
			tmp = result;
			result = ft_strjoin_char(result, token_rm_d_quote[i]);
			free(tmp);
			i ++;
		}
	}
	return (result);
}

static char	*get_size_split_and_malloc(char **split_word)
{
	size_t	new_len;
	int		i;
	char	*merged_token;

	new_len = 0;
	i = 0;
	while (split_word[i] != NULL)
	{
		new_len = ft_strlen(split_word[i]);
//		new_len ++;
//		add this new condition
//		if (split_word[i + 1] != NULL)
//			new_len ++;
		i++;
	}
	merged_token = (char *)malloc(sizeof(char) * (new_len + 1));
	if (merged_token == NULL)
		return (NULL);
//	merged_token[i] = '\0';
	return (merged_token);
}

void	add_space_if_needed(char **split, size_t i, char *merged, size_t *k)
{
	if (split[i + 1] != NULL)
	{
		merged[*k] = SPACE;
		(*k) ++;
	}
}

char	*ft_strjoin_array(char **split_word)
{
	int		i;
	size_t	k;
	char	*merged_token;

	merged_token = get_size_split_and_malloc(split_word);
	if (merged_token == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (split_word[i] != NULL)
	{
//		copy the word to the token array
		copy_word_to_token(split_word[i], merged_token, &k);

//		add spaces if needed
//		add_space_if_needed(split_word, i, merged_token, &k);
		i ++;
	}
	merged_token[k] = '\0';
	return (merged_token);
}
