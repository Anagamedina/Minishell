/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:29:30 by anamedin          #+#    #+#             */
/*   Updated: 2025/01/16 15:38:02 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Initializes a new token node (`t_tokens`).
 *
 * @param str The string to store in the token->str.
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

void	print_list_token_str(t_list *tokens_list)
{
	t_list		*current;
	t_tokens	*token;

	current = tokens_list;
	printf("[");
	while (current != NULL)
	{
		token = (t_tokens *)current->content;
		if (!is_builtin_command(token->str))
		{
			printf("%s", token->str);
			if (current->next != NULL)
				printf("");
		}
		current = current->next;
	}
	printf("]");
	printf("\n");
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
 * Converts a 2D array of strings into a linked list of tokens (`t_list`).
 *
 * @param tokens 2D array of strings (NULL-terminated). Frees `tokens` internally.
 * @return Pointer to the head of the token list, or NULL on allocation failure.
 *
 * @note Each token is initialized with `init_token` and linked using `ft_lstadd_back`.
 *       Errors free allocated memory with `ft_lstclear`.
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

/**
 * Counts consecutive pairs of quotes (double or single) in a string.
 *
 * @param line The input string.
 * @return The number of consecutive quote pairs found.
 */

int	count_consecutive_quotes(const char *line)
{
    int	i;
    int	consecutive_quotes;
    int	inside_quotes;

    i = 0;
    consecutive_quotes = 0;
    inside_quotes = FALSE;
    while (line[i] != '\0')
    {
        if ((line[i] == D_QUOTE && line[i + 1] == D_QUOTE) || \
            (line[i] == S_QUOTE && line[i + 1] == S_QUOTE && \
            inside_quotes == FALSE))
        {
            consecutive_quotes++;
            i ++;
        }
        else if (line[i] == D_QUOTE)
            inside_quotes = !inside_quotes;
        i++;
    }
    return (consecutive_quotes);
}

int	calculate_length_excluding_quotes(char *line)
{
    int	consecutive_quotes;

    consecutive_quotes = count_consecutive_quotes(line);
    return ((int) ft_strlen(line) - (consecutive_quotes * 2));
}

/*
int	calculate_length_excluding_quotes(char *line)
{
	int		i;
	int		consecutives_quotes_counter;
	int		start_dquotes;
	int		end_dquotes;

	i = 0;
	consecutives_quotes_counter = 0;
	start_dquotes = FALSE;
	end_dquotes = FALSE;
	while (line[i] != '\0')
	{
		if ((line[i] == D_QUOTE && line[i + 1] != '\0' \
			&& line[i + 1] == D_QUOTE) || (line[i] == S_QUOTE && \
			line[i + 1] != '\0' && line[i + 1] == S_QUOTE && \
			start_dquotes == FALSE))
			consecutives_quotes_counter ++;
		if (line[i] == D_QUOTE && start_dquotes == FALSE)
		{
			start_dquotes = TRUE;
			end_dquotes = FALSE;
		}
		else if (start_dquotes == TRUE && end_dquotes == FALSE \
			&& line[i] == D_QUOTE)
		{
			end_dquotes = TRUE;
			start_dquotes = FALSE;
		}
		i ++;
	}
	return ((int)ft_strlen(line) - (consecutives_quotes_counter * 2));
}
*/

int	skip_quotes_pairs(char *line, int *i, int *start_dquotes, int *end_dquotes)
{
    int	skipped;

    skipped = 0;
    if ((line[*i] == D_QUOTE && line[*i + 1] == D_QUOTE) ||
        (line[*i] == S_QUOTE && line[*i + 1] == S_QUOTE && \
        *start_dquotes == FALSE))
    {
        *i += 2;
        skipped = 1;
    }
    else if (line[*i] == D_QUOTE && *start_dquotes == FALSE)
    {
        *start_dquotes = TRUE;
        *end_dquotes = FALSE;
    }
    else if (*start_dquotes == TRUE && \
    	*end_dquotes == FALSE && line[*i] == D_QUOTE)
    {
        *end_dquotes = TRUE;
        *start_dquotes = FALSE;
    }
    return (skipped);
}


/**
 * Removes consecutive quotes (single and double) from a string.
 *
 * @param line The input string.
 * @return A new string without consecutive quotes, or NULL if memory allocation fails.
 */

char	*remove_consecutive_quotes(char *line)
{
	int		i;
	int		j;
	int		len;
	char	*new_line;
	int		start_dquotes;
	int		end_dquotes;

	i = 0;
	j = 0;
	len = calculate_length_excluding_quotes(line);
	new_line = malloc(sizeof (char) * (len + 1));
	if (!new_line)
		return (NULL);
	start_dquotes = FALSE;
	end_dquotes = FALSE;
	while (line[i] != '\0')
	{
		if (!skip_quotes_pairs(line, &i, &start_dquotes, &end_dquotes))
		{
			new_line[j] = line[i];
			i ++;
			j ++;
		}
	}
	new_line[j] = '\0';
	return (new_line);
}

/*
char	*clean_consecutive_quotes(char *line)
{
	int		i;
	int		j;
	int		len;
	char	*new_line;
	int		start_dquotes;
	int		end_dquotes;

	len = calculate_length_excluding_quotes(line);
	new_line = malloc(sizeof (char) * (len + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	start_dquotes = FALSE;
	end_dquotes = FALSE;
	while (line[i] != '\0')
	{
		if (line[i] == D_QUOTE && start_dquotes == FALSE)
		{
			start_dquotes = TRUE;
			end_dquotes = FALSE;
		}
		else if (start_dquotes == TRUE && end_dquotes == FALSE && line[i] == D_QUOTE)
		{
			end_dquotes = TRUE;
			start_dquotes = FALSE;
		}
		if ((line[i] == D_QUOTE && line[i + 1] != '\0' && line[i + 1] == D_QUOTE) || \
			(line[i] == S_QUOTE && line[i + 1] != '\0' && line[i + 1] == S_QUOTE  && start_dquotes == FALSE))
		{
			i += 2;
		}
		else
		{
			new_line[j] = line[i];
			i ++;
			j ++;
		}
	}
	new_line[j] = '\0';
	return (new_line);
}
*/

/*
 * ORIGINAL FUNCTION
char	*clean_consecutive_quotes(const char *line)
{
	int		i;
	int		j;
	int		len;
	int		consecutives_quotes_counter;
	char	*new_line;
	int		start_dquotes;
	int		end_dquotes;

	i = 0;
	len = 0;
	consecutives_quotes_counter = 0;
	start_dquotes = FALSE;
	end_dquotes = FALSE;

	while (line[i] != '\0')
	{
		if ((line[i] == D_QUOTE && line[i + 1] != '\0' && line[i + 1] == D_QUOTE) || \
			(line[i] == S_QUOTE && line[i + 1] != '\0' && line[i + 1] == S_QUOTE && start_dquotes == FALSE))
			consecutives_quotes_counter ++;
		if (line[i] == D_QUOTE && start_dquotes == FALSE)
		{
			start_dquotes = TRUE;
			end_dquotes = FALSE;
		}
		else if (start_dquotes == TRUE && end_dquotes == FALSE && line[i] == D_QUOTE)
		{
			end_dquotes = TRUE;
			start_dquotes = FALSE;
		}
		i ++;
	}
	len = (int)ft_strlen(line) - (consecutives_quotes_counter * 2);
	new_line = malloc(sizeof (char) * (len + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	j = 0;
	start_dquotes = FALSE;
	end_dquotes = FALSE;
	while (line[i] != '\0')
	{
		if (line[i] == D_QUOTE && start_dquotes == FALSE)
		{
			start_dquotes = TRUE;
			end_dquotes = FALSE;
		}
		else if (start_dquotes == TRUE && end_dquotes == FALSE && line[i] == D_QUOTE)
		{
			end_dquotes = TRUE;
			start_dquotes = FALSE;
		}
		if ((line[i] == D_QUOTE && line[i + 1] != '\0' && line[i + 1] == D_QUOTE) || \
			(line[i] == S_QUOTE && line[i + 1] != '\0' && line[i + 1] == S_QUOTE  && start_dquotes == FALSE))
		{
			i += 2;
		}
		else
		{
			new_line[j] = line[i];
			i ++;
			j ++;
		}
	}
	new_line[j] = '\0';
	return (new_line);
}
 */
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
	char	**token_array;
	t_list	*tokens_list;
	char	*processed_line;

	tokens_list = NULL;
	token_array = NULL;
	processed_line = remove_consecutive_quotes(line);
	if (!processed_line)
	{
		printf("Error: Failed to clean the input line\n");
		return (NULL);
	}
	printf("Processed line: [%s]\n", processed_line);
	token_array = ft_split_quote(processed_line);
	if (token_array == NULL)
	{
		printf("Error: Tokenization failed\n");
		// free(token_array);
		return (NULL);
	}
	printf("****** Tokens AFTER SPLIT ******\n");
	int i = 0;
	while (token_array[i] != NULL)
	{
		printf("[%d] [%s]\n", i, token_array[i]);
		i ++;
	}
	printf("--------------------------------\n");

	tokens_list = convert_tokens_to_list(token_array);
	if (tokens_list == NULL)
	{
		printf ("Error: Failed to generate token list\n");
		/* ft_lstclear(&tokens_list, free);*/
		return (NULL);
	}
	print_list_token(tokens_list);
	// ft_free_array(token_array);
	identify_commands(tokens_list);
	return (tokens_list);
}

