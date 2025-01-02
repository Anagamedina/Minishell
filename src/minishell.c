/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/16 17:59:01 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*input;
	t_mini	*minishell;

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
			printf("Error al leer el input\n");
			free(input);
			continue ;
		}
		minishell->token = generate_token_list(input, minishell);
		if (minishell->token == NULL)
		{
			printf("Error al generar la lista de tokens.\n");
			continue ;
		}
		//identify_commands(minishell->token, minishell->exec->paths);
		parser_tokens(minishell);
		printf("Lista de tokens:\n");
		//iprint_list_token(minishell->token);
		// Crear la lista de comandos
		minishell->exec = init_exec(envp);

		if (!minishell->exec)
		{
			perror("Error al inicializar t_exec");
			return 1;
		}

		minishell->exec->first_cmd = create_cmd_list(minishell->token, minishell->exec->paths);
		add_details_to_cmd_list(minishell->exec->first_cmd, minishell->token, NULL);
		print_list_commands(minishell->exec->first_cmd);
		print_list_token_str(minishell->token);
		 //cases_builtins(minishell);
	}
	return (0);
}
