/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:19 by anamedin          #+#    #+#             */
/*   Updated: 2025/01/28 12:05:30 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_input(void)
{
	char	*input;

	input = readline("minishell> ");
	if (input && *input)
	{
		add_history(input);
	}
	return (input);
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
