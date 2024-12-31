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

/*int	main(int argc, char **argv, char **envp)
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
		minishell->token = generate_token_list(input);
		if (minishell->token == NULL)
		{
			printf("Error al generar la lista de tokens.\n");
			continue ;
		}
		parser_tokens(minishell);
		printf("Lista de tokens:\n");
		print_list_token_str(minishell->token);
		// Crear la lista de comandos
		minishell->exec->first_cmd = create_cmd_list(minishell->token, minishell->exec->paths);
		printf("Lista de comandos:\n");
		print_list_commands(minishell->exec->first_cmd);
		print_list_token(minishell->token);
		 //cases_builtins(minishell);
	}
	return (0);
}*/

int main(int argc, char **argv, char **envp)
{
	t_exec *exec_info;
	t_list *cmd_list;
	t_tokens *tokens;  // Suponiendo que tokens ya esté inicializado
	int exec_pipe[2];  // Para pipes, si es necesario

	// Inicializamos la estructura exec_info con las rutas del PATH
	exec_info = init_exec(envp);

	// Si no se pudo inicializar correctamente la estructura exec_info
	if (!exec_info)
	{
		perror("Error al inicializar t_exec");
		return 1;
	}

	// Crear la lista de comandos
	cmd_list = create_cmd_list(tokens->token_list, exec_info->paths);

	// Añadir detalles a la lista de comandos (como las redirecciones, pipes, etc.)
	add_details_to_cmd_list(cmd_list, tokens->token_list, exec_pipe);

	// ... Resto del código para ejecutar los comandos, redirecciones, etc.

	// Liberar memoria
	//free_exec(exec_info);  // Función que libere la memoria de t_exec
	return 0;
}
