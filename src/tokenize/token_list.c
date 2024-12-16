/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:29:30 by anamedin          #+#    #+#             */
/*   Updated: 2024/12/16 18:17:54 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Initializes a new token node (`t_tokens`).
 *
 * @param str The string to store in the token.
 * @param token_type The type of the token.
 * @return A pointer to the new token, or NULL if memory allocation fails.
 */

t_tokens	*init_token(char *str, int token_type)
{
	t_tokens	*new_token;

	new_token = malloc(sizeof(t_tokens));
	if (!new_token)
		return (NULL);
	new_token->str = ft_strdup(str);
	new_token->type_token = token_type;
	new_token->length = ft_strlen(str);
	new_token->id_token = -1;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

/**
 * Prints all tokens in a linked list (`t_list`).
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

/*
int	check_lowercase_tokens(t_list *tokens_list)
{
	t_list		*current;
	t_tokens	*token;
	int 		i;

	current = tokens_list;
	while (current->next != NULL)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == WORD)
		{
			i = 0;
			while (token->str[i])
			{
				if (token->str[i] < 'a' || token->str[i] > 'z')
					return (FALSE);
				i++;
			}
		}
		current = current->next;
	}
	return (TRUE);
}
*/

/**
 * Converts an array 2D of strings into a linked list of tokens (`t_list`),
 * where each node contains a `t_tokens` structure representing a token.
 * @see init_token: Function to create tokens with their type and content.
 * @see ft_lstadd_back: Links tokens into a list using.
 * Returns the token list or NULL if memory allocation fails.
 */

t_list	*tokenize_list(char **tokens)
{
	t_list		*tokens_list;
	t_tokens	*new_token;
	t_list		*new_node;
	int			i;

	tokens_list = NULL;
	if (tokens == NULL)
		return (NULL);
	i = 0;
	while (tokens[i] != NULL)
	{
		new_token = init_token(tokens[i], set_token_type(tokens[i]));
		new_token->id_token = i;
		new_node = ft_lstnew(new_token);
		if (!new_node)
		{
			free(new_token);
			ft_lstclear(&tokens_list, free);
			return (NULL);
		}
		ft_lstadd_back(&tokens_list, new_node);
		i++;
	}
	free(tokens);
	return (tokens_list);
}

//	**********MAIN FUNCTION***************/
/**
 * Splits the input line into tokens, processes quotes,
 * and creates a linked list of tokens.
 * Returns the token list or NULL on error.
 */

t_list	*generate_token_list(char *line)
{
	char	**tokens;
	t_list	*tokens_list;

	tokens_list = NULL;
	tokens = NULL;
	tokens = ft_split_quote(line);
	if (tokens == NULL)
	{
		free(tokens);
		return (NULL);
	}
	tokens_list = tokenize_list(tokens);
	if (tokens_list == NULL)
	{
		ft_lstclear(&tokens_list, free);
		return (NULL);
	}
	identify_commands(tokens_list);
	return (tokens_list);
}
