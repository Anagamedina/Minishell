/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/16 15:38:16 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_mini	*minishell;

	(void) argc;
	(void) argv;
	minishell = init_mini_list(envp);

	input = NULL;
	if (minishell == NULL)
	{
		printf("Error al inicializar minishell.\n");
		return (1);
	}
	while (1)
	{
		input = read_input();
		if (!input || !check_quotes_line(input))
		{
			printf("Error: quotes are incorrect\n");
			free(input);
			continue ;
		}
		minishell->token = generate_token_list(input);
		if (minishell->token == NULL)
			continue ;
		parser_tokens(minishell);
		// print_list_token(minishell->token);
		print_list_token(minishell->token);
		// minishell->cmds = add_tokens_to_linked_list_commands(minishell->token);
		// print_list_commands(minishell->cmds);
		// print_list_token(minishell->token);
		//cases_builtins(minishell);
	}
	return (0);
}
