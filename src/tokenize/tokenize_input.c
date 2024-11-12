/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:43 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/12 13:30:46 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Retorno: Un array de strings,
 * donde cada elemento es un token
 *
 * tokens[0] = "echo";
tokens[1] = "hello world"; // Comillas gestionadas como un solo token
tokens[2] = "|";
tokens[3] = "grep";
tokens[4] = "hello";
tokens[5] = ">";
tokens[6] = "output.txt";
tokens[7] = NULL;
.*/

char **tokenize_input(char *input)
{
	if (!check_quotes_line(input))
	{
		printf("Error: Unmatched quotes in the input.\n");
		return NULL;
	}
	char **tokens = ft_split_quote(input);
	return (tokens);
}
