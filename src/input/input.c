/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:19 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/28 11:10:32 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline("minishell> ");
	if (!input)
	{
		ft_putendl_fd("exit", 1);
		// TODO: liberar todo aqui y salir
		exit(0);
		// return (NULL);
	}
	// if (*input)
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

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/**
 * @brief check if the input contains quotes and if the number of quotes is even
 */
int	check_quotes_line(const char *line)
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
