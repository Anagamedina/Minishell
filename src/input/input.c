/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:19 by anamedin          #+#    #+#             */
/*   Updated: 2025/01/08 11:00:27 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "prototype.h"

char	*read_input(void)
{
	char *input;

	input = readline("minishell> "); // Muestra el prompt y lee la entrada
	if (input && *input)
	{
		add_history(input);
	}
	return (input);
}

/*
 * comprobar que si se encuentra el caracter "
 * ha de encontrar otro que es el que cierra "
 * "hello!"
 * Verificar si empieza y termina con comillas dobles
*/
int	check_quotes_line(const char *line)
{
	int i;
	int double_quotes;
	int single_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i] != '\0')
	{
		if (line[i] == D_QUOTE)
			double_quotes ++;
		else if (line[i] == S_QUOTE)
			single_quotes ++;
		i++;
	}
	// Verificamos que ambos contadores de comillas sean pares
	if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
		return (FALSE);
	return (TRUE);
}

/**	echo "" hello ""
 * [0] = echo
 * [1] = "" hello ""
 * [2] = NULL
 */

void	check_final_dquote(const char *line, int *i)
{
	// (*i)++;
	while (line[*i])
		(*i)++;
	if (line[*i] == D_QUOTE)
		(*i)++;
}

void	get_size_words_with_pivote(const char *line)
{
	int i;
	int double_quotes;
	int single_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i] != '\0')
	{
		if (line[i] == D_QUOTE)
		{
			// try to find the last dquote in the line
			check_final_dquote(line, &i);

		}
		else if (line[i] == S_QUOTE)
		{

		}
		i++;
	}
}
