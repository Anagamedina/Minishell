/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/30 00:00:24 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*input;
	t_mini	*minishell;

	minishell = NULL;
	minishell = init_mini_list(envp);

	if (minishell == NULL)
	{
        fprintf(stderr, "Error: Failed to initialize environment list.\n");
		// printf("Error al inicializar minishell.\n");
		free(minishell);
		// return (1);
		return (EXIT_FAILURE);
	}
	input = NULL;
	// echo "the user: $USER in level: $SHLVL " 'cReAtE_This_minishell' :)
	while (1)
	{
		input = read_input();
		if (!input || !check_quotes_line(input))
		{
			printf("Error: fail reading input.\n");
			free(input);
			break ;
		}
		minishell->token = generate_token_list(input);
		if (minishell->token == NULL)
		{
			perror("Error: generating the list of tokens.\n");
			continue ;
		}
		// free(input);
		/*
		minishell->exec = init_exec(minishell->env);
		if (!minishell->exec)
		{
			perror("Error al inicializar t_exec");
			return (1);
		}
		*/
		parser_tokens(minishell);
		print_list_token_str_one_line(minishell->token);
		/*
		minishell->exec->first_cmd = create_cmd_list(minishell->token, minishell->exec->paths);
		if (!minishell->exec->first_cmd)
		{
			printf("Error al crear la lista de comandos.\n");
			continue ;
		}

		add_details_to_cmd_list(minishell->exec->first_cmd, minishell->token);

		if (execute_commands(minishell) != TRUE)
		{
			free_cmd_list(minishell->exec->first_cmd);
			free(minishell);
			continue;
		}
		else
			continue;
		*/
		//free_cmd_list(minishell->exec->first_cmd);
		//cases_builtins(minishell);
		// free(minishell->token);
		// free_tokens((t_tokens *)minishell->token);
	}
	free_mini(minishell);
	/*
	if (input != NULL)
	{
        free(input);
	}
	*/
	return (0);
}

/*
printf("PID PADRE: [%d]\n", getpid());
int pipe_fd[2];
if  (pipe(pipe_fd) == -1)
{
	perror("Pipe");
	exit(EXIT_FAILURE);
}

int i = 0;
while (i < 2)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("Error creando proceso hijo");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		// Proceso hijo
		printf("Proceso hijo ejecutándose\n");
		printf("PID HIJO: %d\n", getpid());
		if (i == 0)
		{
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			{
				char message[256];
				snprintf(message, sizeof(message), "Error redirigiendo salida hijo PID: %d", getpid());
				perror(message);
				exit(EXIT_FAILURE);
			}
			// Cerrar descriptores no necesarios
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			char *args[] = {"ls",  NULL};
			if (execve("/usr/bin/ls", args, envp) == -1)
			{
				perror("Error mutando a ls");
				exit(EXIT_FAILURE);
			}
		}
		else if (i == 1)
		{
			if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			{
				char message[256];
				snprintf(message, sizeof(message), "Error redirigiendo salida hijo PID: %d", getpid());
				perror(message);
				exit(EXIT_FAILURE);
			}
			// Cerrar descriptores no necesarios
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			char *args[] = {"wc",  NULL};
			if (execve("/usr/bin/wc", args, envp) == -1)
			{
				perror("Error mutando a wc");
				exit(EXIT_FAILURE);
			}
		}
	}
	i++;
}

// Cerrar descriptores no necesarios en el proceso padre
close(pipe_fd[0]);
close(pipe_fd[1]);

// Proceso padre
waitpid(-1, NULL, 0);

return 1;
*/


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


