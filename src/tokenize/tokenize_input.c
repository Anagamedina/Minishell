/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                   :+:      :+:    :+:   */
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

char	**tokenize_line(char *line)
{
	char	**tokens;

	tokens = NULL;
	tokens = ft_split_quote(line);
	return (tokens);
}
