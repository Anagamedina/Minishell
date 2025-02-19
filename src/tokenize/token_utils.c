/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:26:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/19 21:53:17 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"


t_tokens	*init_token(char *str, int token_type)
{
	t_tokens	*new_token;

	if (!str)
		return (NULL);
	new_token = NULL;
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
	new_token->length = ft_strlen(str);
	new_token->id_token = -1;
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
			ft_lstclear(&token_list, free);
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
	free_split_result_struct(tokens_array, count_words(tokens_array));
	free(tokens_array);
	return (tokens_list);
}
	/*
	if (!tokens_list)
	{
		free_split_result_struct(tokens_array, count_words(tokens_array));
		free(tokens_array);
		return (NULL);
	}
	free_split_result_struct(tokens_array, count_words(tokens_array));
	free(tokens_array);
	*/

/**
 * Print all tokens in a linked list (t_list).
 *
 * @param tokens_list Pointer to the head of the token list.
 */

void	print_list_token(t_list *tokens_list)
{
	t_list		*current;
	t_tokens	*token;
	int			i;

	current = tokens_list;
	i = 1;
	while (current != NULL)
	{
		token = (t_tokens *)current->content;
		printf("TOKEN [%i] :\n", i);
		printf("str: [%s]\n", token->str);
		printf("type: [%i]\n", token->type_token);
		printf("len: [%zu]\n", token->length);
		i ++;
		current = current->next;
		printf("-------------------\n");
	}
}