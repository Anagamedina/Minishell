/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/01 23:04:39 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char** argv, char** envp)
{
	(void)argc;
	(void)argv;
	char* input;
	t_mini* minishell;


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
			break;
		}
		minishell->token = generate_token_list(input);
		// print_list_token_str(minishell->token);

		if (minishell->token == NULL)
		{
			printf("Error al generar la lista de tokens.\n");
			continue;
		}
		// print_list_token_str(minishell->token);
		minishell->exec = init_exec(minishell->env);
		if (!minishell->exec)
		{
			perror("Error al inicializar t_exec");
			return 1;
		}
		update_words_in_tokens(minishell);
		parser_tokens(minishell);

		if(parse_redir(minishell) == FALSE)
		{
			printf("Error al parsear las redirecciones.\n");
			continue;
		}
		minishell->exec->first_cmd = create_cmd_list(minishell->token, minishell->exec->paths);

		if (!minishell->exec->first_cmd)
		{
			printf("Error al crear la lista de comandos.\n");
			continue;
		}

		add_details_to_cmd_list(minishell->exec->first_cmd, minishell->token);

		if (execute_commands(minishell) == FALSE)
		{
			free_cmd_list(minishell->exec->first_cmd);
			free(minishell);
			continue;
		}
		else
			continue;
	}
	//free_cmd_list(minishell->exec->first_cmd);
	return (0);
}









/*static void free_token_list(t_list *tokens) {
	t_list *current = NULL;
	t_tokens *token_data;

	while (current->next != NULL)
	{
		token_data = (t_tokens *)tokens->content;
		if (token_data->next) // Si hay siguiente token
		{
			free(token_data->str);// Libera la cadena asociada al token
		}
		free(token_data); // Libera el nodo actual
		current = current->next; // Avanza al siguiente token
	}
}*/


