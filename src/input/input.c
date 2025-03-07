/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:19 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 20:45:58 by anamedin         ###   ########.fr       */
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

/*char	*read_input(void)
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
		if (!temp)
		{
			free(input);
			write(2, "minishell: unexpected EOF while looking for matching quote\n", 58);
			return (NULL);
		}
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
		if (!input)
			return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}
*/

char	*read_input(t_mini *mini)
{
	char	*input;
	char	*new_input;
	char	*temp;

	input = readline("minishell> ");
	if (!input)
	{
		write(2, "exit\n", 5);
		free_mini(mini);
		exit(0);
	}
	while (!check_quotes_line(input))
	{
		temp = readline("> ");
		if (!temp)
		{
			free(input);
			write(2, "minishell: unexpected EOF while looking for matching quote\n", 58);
			free_mini(mini); // ✅ Asegurar que liberamos `mini`
			exit(1);
		}
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
		if (!input)
			return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}

/*void	configure_terminal(void)
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
}*/

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
		if (line[i] == '"' && !in_single)
			in_double = !in_double;
		else if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		i++;
	}
	if (in_single || in_double)
		return (FALSE);
	return (TRUE);
}