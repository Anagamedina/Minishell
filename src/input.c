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

#include "../includes/minishell.h"







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