/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:26:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 17:25:31 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokens	*init_token(char *str, int token_type)
{
	t_tokens	*new_token;

	if (!str)
		return (NULL);
	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return (NULL);
	new_token->str = ft_strdup(str);
	if (!new_token->str)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type_token = token_type;
	new_token->length = ft_strlen(new_token->str);
	new_token->id_token = -1;
	new_token->is_valid_cmd = FALSE;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

static int	count_words(char **tokens_array)
{
	int	count;

	count = 0;
	if (!tokens_array)
		return (0);
	while (tokens_array[count])
		count ++;
	return (count);
}

t_list	*convert_tokens_to_list(char **tokens)
{
	t_list		*token_list;
	t_tokens	*curr_token;
	t_list		*node_to_add;
	int			i;

	token_list = NULL;
	if (tokens == NULL)
		return (NULL);
	i = 0;
	while (tokens[i] != NULL)
	{
		curr_token = init_token(tokens[i], set_token_type(tokens[i]));
		curr_token->id_token = i;
		node_to_add = ft_lstnew(curr_token);
		if (!node_to_add)
		{
			free(curr_token);
			ft_lstclear(&token_list, free_tokens_void);
			return (NULL);
		}
		ft_lstadd_back(&token_list, node_to_add);
		i ++;
	}
	return (token_list);
}

t_list	*generate_token_list(char *line)
{
	char	**tokens_array;
	t_list	*tokens_list;
	char	*processed_line;

	tokens_list = NULL;
	tokens_array = NULL;
	processed_line = remove_consecutive_quotes(line);
	if (!processed_line)
		return (NULL);
	tokens_array = ft_split_quotes(processed_line);
	free(processed_line);
	if (!tokens_array)
		return (NULL);
	tokens_list = convert_tokens_to_list(tokens_array);
	free_partial_split(tokens_array, count_words(tokens_array));
	free(tokens_array);
	return (tokens_list);
}
