/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:19 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/03 00:40:33 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	control_and_d(char *line)
{
	if (!line)
	{
		if (!isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "exit\n", 5);
		write(STDOUT_FILENO, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
}

char	*read_input(void)
{
	char	*input;
	char	*new_input;
	char	*temp;

	input = readline("minishell> ");
	if (!input) // Si `Ctrl+D` se presiona en el prompt principal
	{
		write(2, "exit\n", 5);
		exit(0);
	}
	while (!check_quotes_line(input))
	{
		temp = readline("> ");
		if (!temp)  //Si Ctrl+D en prompt secundario, error y salida
		{
			free(input);
			write(2, "minishell: unexpected EOF while looking for matching quote\n", 58);
			return (NULL);
		}
		// Si `Ctrl+C` fue presionado, `readline` devuelve una línea vacía
		if (ft_strlen(temp) == 0)
		{
			free(temp);
			write(2, "\n", 1);
			return (NULL);
		}
		new_input = ft_strjoin(input, "\n");
		if (!new_input)
		{
			free(input);
			free(temp);
			return (NULL);
		}
		free(input);
		input = ft_strjoin(new_input, temp);
		free(new_input);
		free(temp);
		if (!input) // ✅ Verificar que `ft_strjoin()` no haya devuelto `NULL`
			return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}

/**
 * @brief configure the terminal

 * term.c_lflag &= ~ECHOCTL (off the print control characters in the input)

 * isatty(STDIN_FILENO): Verify if minishell is running in a terminal.

 * ttyname(STDIN_FILENO): show the name of the terminal.

 * tcgetattr() and tcsetattr():

 * modify the terminal attributes to Ctrl+C not to print ^C.
 *
 */
void	configure_terminal(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
		printf("Running in a terminal: %s\n", ttyname(STDIN_FILENO));
	else
		printf("Not running in a terminal\n");

	if (tcgetattr(STDIN_FILENO, &term) == -1)
		return ;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}


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