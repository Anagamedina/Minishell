/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:26:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/28 17:10:00 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:29:30 by anamedin          #+#    #+#             */
/*   Updated: 2025/01/24 16:24:54 by dasalaza         ###   ########.fr       */
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

/**
 * Converts a 2D array of strings into a linked list of tokens (`t_list`).
 *
 * @note Each token is initialized with `init_token`
 * and linked using `ft_lstadd_back`.
 * Errors free allocated memory with `ft_lstclear`.
 */

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
	free(tokens);
	return (token_list);
}

//**********MAIN FUNCTION**********************/

/**
 * Splits the input line into tokens, handles quotes,
 * and generates a linked list of tokens.
 *
 * Steps:
 * 1. Clean consecutive quotes in the input line.
 * 2. Split the line into tokens considering quotes and special characters.
 * 3. Tokenize the split tokens into a linked list.
 * 4. Identify and mark commands within the token list.
 *
 * @example [echo ' qwerty' $USER" hello"]
 * @see clean_consecutive_quotes: Function to clean consecutive quotes.
 * @see ft_split_quote: Function to split the input line into tokens.
 * @see tokenize_list: Function to tokenize the input line into a token list.
 * @see identify_commands: Function to classify commands in the token list.
 *
 * @returns A linked list of tokens or NULL on error.
 */

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
	// printf("Processed line: [%s]\n", processed_line);
	tokens_array = ft_split_quotes(processed_line);
	free(processed_line);

	if (tokens_array == NULL)
		return (NULL);

	tokens_list = convert_tokens_to_list(tokens_array);
	if (tokens_list == NULL)
		return (NULL);

	return (tokens_list);
}
