/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 21:03:47 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 22:07:03 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:00:41 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 01:26:54 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes_line(const char *line)
{
	int	i;
	int	in_single;
	int	in_double;

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

/* setup_signals(PARENT);*/
char	*read_input(t_mini *mini)
{
	char	*line;

	line = readline("minishell> ");
	if (!line)
	{
		write(1, "exit\n", 5);
		mini->exit_status = 0; // Asegurar que $? sea 0
		free_mini(mini);
		rl_clear_history();
		exit(0);
	}
	if (*line)
		add_history(line);
	return (line);
}
/**
tmp = handle_unclosed_quotes(line, mini);
if (!tmp)
{
	free(line);
	return (NULL);
}
*/
/*
static void	handle_unexpected_eof(char *input, t_mini *mini)
{
	free(input);
	ft_putendl_fd("minishell: unexpected EOF \
	while looking for matching quote", 2);
	free_mini(mini);
	exit(1);
}

static char	*concatenate_input(char *input, char *temp)
{
	char	*new_input;
	char	*result;

	new_input = ft_strjoin(input, "\n");
	free(input);
	if (!new_input)
	{
		free(temp);
		return (NULL);
	}
	result = ft_strjoin(new_input, temp);
	free(new_input);
	free(temp);
	return (result);
}

*/
/*
char	*handle_unclosed_quotes(char *input, t_mini *mini)
{
	char	*temp;
	char	*new_input;

	while (!check_quotes_line(input))
	{
		temp = readline("> ");
		if (!temp)
			handle_unexpected_eof(input, mini);

		if (ft_strlen(temp) == 0)
		{
			free(temp);
			continue;
		}
		new_input = concatenate_input(input, temp);
		if (!new_input)
		{
			free(input);
			return (NULL);
		}
		input = new_input; // ✅ Asignamos correctamente la nueva memoria
	}
	return (input);
}*/
