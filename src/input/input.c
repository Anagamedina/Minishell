/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:19 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/07 13:48:39 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_input(void)
{
	char *input;
	while (1)
	{
		input = readline("minishell> "); // Muestra el prompt y lee la entrada
		if (input == NULL)
		{
			// Si el usuario presiona Ctrl+D, salimos del bucle
			printf("\nExiting minishell.\n");
			continue;
		}

		if (input && *input)
		{
            add_history(input);
			printf("You entered: %s\n", input);
		}
		free(input);
	}
	return (input);
}

/*
 * comprobar que si se encuentra el caracter "
 * ha de encontrar otro que es el que cierra "
 * "hello!"
 Verificar si empieza y termina con comillas dobles
*/
int check_quotes_line(char *line)
{
	int i = 0;
	int double_quotes = 0;
	int single_quotes = 0;

	while (line[i])
	{
		if (line[i] == '"')
			double_quotes++;
		else if (line[i] == '\'')
			single_quotes++;
		i++;
	}
	// Verificamos que ambos contadores de comillas sean pares
	if (double_quotes % 2 != 0)
	{
		return (0);
	}
	if (single_quotes % 2 != 0)
	{
		printf("Error: Unmatched single quotes in the input.\n");
		return (0);
	}
	return (1);
}


/*
 * VERIFICAR el patron
 * comanddo (opciones) [argumentos]
 *KEY=VALUE
*/

//aux function
static char	*ft_epur(char *str)
{
	int		i = 0;
	int		j = 0;
	char	*result;

	result = malloc(sizeof(char) * (strlen(str) + 1));
	if (!result)
		return (NULL);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			result[j++] = str[i++];
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] != '\0')
			result[j++] = ' ';
	}
	result[j] = '\0';
	return (result);
}

/*
 * TODO daruny: terminar esta funcion
 * checkear el orden la linea: comando option argumento
 * echo -n abcd
 */
int	check_syntax_order(char *line)
{
	int 	i;
	char	*clean_line;
	int 	flag;

	clean_line = ft_epur(line);
	i = 0;
	flag = 0;
	while (clean_line[i] != '\0')
	{
//		comando
		if (ft_isalpha(clean_line[i]) == 1)
		{
			while (ft_isalpha(clean_line[i]) == 1)
				i++;
		}
		if (clean_line[i] == ' ' && clean_line[i + 1] == '-')
		{
			flag = 1;  // Se ha encontrado una opción de comando
			i++;       // Saltar el guion '-'
			while (clean_line[i] && ft_isalpha(clean_line[i]) == 1)
				i++;
		}
		else if (clean_line[i] == ' ' && ft_isalpha(clean_line[i + 1]) == 1)
		{
			flag = 0;
			while (clean_line[i] && ft_isalpha(clean_line[i]) == 1)
				i++;
		}
		else
			i++;
	}
	free(clean_line);
	return (flag);
}

void	validate_input(char *line)
{
	if (check_quotes_line(line) == 0)
		printf("Error: Unmatched double quotes in the input.\n");
	else if (check_syntax_order(line) == 1)

}