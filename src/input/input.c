/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:19 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/27 19:45:53 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"




/*char	*read_multiline_input(char *input)
{
	char	*new_input;
	char	*temp;

	while (check_quotes_line(input))
	{
		temp = readline("> ");  // 🔹 Prompt secundario como Bash
		if (!temp)  // Si el usuario presiona Ctrl+D, cancelamos
		{
			free(input);
			write(2, "minishell: unexpected EOF while looking for matching quote\n", 58);
			return (NULL);
		}
		new_input = ft_strjoin(input, "\n");  // Agregar salto de línea
		free(input);
		input = ft_strjoin(new_input, temp);  // Concatenar entrada nueva
		free(new_input);
		free(temp);
	}
	return (input);
}*/

char	*read_input(void)
{
	char	*input;
	char	*new_input;
	char	*temp;

	input = readline("minishell> ");
	if (!input)  // 🔹 Manejo de Ctrl+D en la primera entrada
	{
		write(2, "exit\n", 5);
		return (NULL);
	}

	// 🔹 Si hay comillas abiertas, pedir más input
	while (!check_quotes_line(input))  // 🔹 Antes estaba al revés
	{
		temp = readline("> ");  // 🔹 Prompt secundario (`>`)
		if (!temp)  // 🔹 Si Ctrl+D en prompt secundario, error y salida
		{
			free(input);
			write(2, "minishell: unexpected EOF while looking for matching quote\n", 58);
			return (NULL);
		}
		new_input = ft_strjoin(input, "\n");  // 🔹 Agregar salto de línea
		free(input);
		input = ft_strjoin(new_input, temp);  // 🔹 Concatenar nueva entrada
		free(new_input);
		free(temp);
	}

	if (*input)
		add_history(input);

	return (input);
}

/*int	check_quotes_line(const char *line)
{
	int	i;
	int	double_quotes;
	int	single_quotes;

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
	if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
		return (FALSE);
	return (TRUE);
}
*/

int	check_quotes_line(const char *line)
{
	int	i;
	int in_single;
	int in_double;

	i = 0;
	in_single = 0;
	in_double = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '"' && !in_single)  // Solo contar si no estamos en comillas simples
			in_double = !in_double;
		else if (line[i] == '\'' && !in_double)  // Solo contar si no estamos en comillas dobles
			in_single = !in_single;
		i++;
	}
	// Si hay una comilla sin cerrar, devolver FALSE
	if (in_single || in_double)
		return (FALSE);
	return (TRUE);
}