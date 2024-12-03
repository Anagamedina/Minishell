/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:19 by anamedin          #+#    #+#             */
/*   Updated: 2024/12/03 12:38:10 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_input(void)
{
	char *input;

	input = readline("minishell> "); // Muestra el prompt y lee la entrada
	if (input && *input)
	{
		add_history(input);
		//printf("line: %s\n", input);
	}
	return (input);
}

/*
 * comprobar que si se encuentra el caracter "
 * ha de encontrar otro que es el que cierra "
 * "hello!"
 * Verificar si empieza y termina con comillas dobles
*/
int	check_quotes_line(char *line)
{
	int i;
	int double_quotes;
	int single_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			double_quotes++;
		else if (line[i] == '\'')
			single_quotes++;
		i++;
	}
	// Verificamos que ambos contadores de comillas sean pares
	if (double_quotes % 2 != 0)
		return (0);
	if (single_quotes % 2 != 0)
	{
		//printf("Error: Unmatched single quotes in the input.\n");
		return (2); //indica error pero se va a la funcion que ese llama
	}
	return (1);
}


