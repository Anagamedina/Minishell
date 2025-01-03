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
		parser_tokens(minishell);
		printf("Lista de comandos:\n");
		minishell->exec = init_exec(envp);

		if (!minishell->exec)
		{
			perror("Error al inicializar t_exec");
			return 1;
		}
		// TODO: create in print exec
		minishell->exec->first_cmd = create_cmd_list(minishell->token, minishell->exec->paths);
		if (!minishell->exec->first_cmd)
		{
			printf("Error al crear la lista de comandos.\n");
			continue ;
		}
		add_details_to_cmd_list(minishell->exec->first_cmd, minishell->token);
		print_list_commands(minishell->exec->first_cmd);
		printf("Lista de tokens:\n");
		print_list_token_str(minishell->token);
		//execute_commands(minishell);
		handle_commands(minishell);
		free_cmd_list(minishell->exec->first_cmd);
		 //cases_builtins(minishell);
	}
	return (0);
}

/*int	process_input(t_mini *mini, char *input)
{
	mini->token = generate_token_list(input, mini);
	if (!mini->token)
	{
		fprintf(stderr, "Error al generar la lista de tokens.\n");
		return (0);
	}

	parser_tokens(mini);
	mini->exec->first_cmd = create_cmd_list(mini->token, mini->exec->paths);
	if (!mini->exec->first_cmd)
	{
		fprintf(stderr, "Error al crear la lista de comandos.\n");
		//free_token_list(mini->token);
		return (0);
	}

	if (add_details_to_cmd_list(mini->exec->first_cmd, mini->token) == -1)
	{
		fprintf(stderr, "Error al añadir detalles a la lista de comandos.\n");
		free_cmd_list(mini->exec->first_cmd);
		//free_token_list(mini->token);
		return (0);
	}

	execute_commands(mini);
	free_cmd_list(mini->exec->first_cmd);
	//free_token_list(mini->token);
	return (1);
}







int	main(int argc, char **argv, char **envp)
{
	t_mini	*minishell;
	char	*input;

	minishell = init_mini_list(envp);
	if (!minishell)
	{
		perror("Error al inicializar minishell");
		return (EXIT_FAILURE);
	}

	while (1)
	{
		input = read_input();
		if (!input || !check_quotes_line(input))
		{
			fprintf(stderr, "Error en el input o comillas mal balanceadas.\n");
			free(input);
			continue;
		}

		if (!process_input(minishell, input))
		{
			fprintf(stderr, "Error procesando el input.\n");
			free(input);
			continue;
		}
		free(input);
	}
	//cleanup_mini(minishell);
	return (EXIT_SUCCESS);
}
*/