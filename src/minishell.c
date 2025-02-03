/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 19:49:16 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 19:37:55 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/31 17:57:12 by  dasalaza        ###   ########.fr       */
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
	if (!minishell)
	{
		perror("Error: init minishell.\n");
		free(minishell);
		return (1);
	}
	while (1)
	{
		input = read_input();
		if (!input || !check_quotes_line(input))
		{
			printf("Error: fail reading input.\n");
			free(input);
			break ;
		}

		//	TOKENS
		//echo $DISPLAY $USERNAME "123" $HOME 'abc' '$HOME'
		// echo $DISPLAY $USERNAME "123" $HOME 'abc' $SHELL """abcd""" $123456 incomplete$HOMEabc $'tab\there'
		// echo $'hello\t' ana is a te\\nst in minishell

		if (minishell->tokens)
			free_tokens(minishell->tokens);
		minishell->tokens = generate_token_list(input);

		if (!minishell->tokens)
		{
			perror("Error al generar la lista de tokens.\n");
			free(input);
			continue ;
		}

		parser_tokens(minishell);

		//	EXEC
		if (minishell->exec)
			free_exec(minishell->exec);
		minishell->exec = init_exec(minishell->env);
		if (!minishell->exec)
		{
			perror("Error al inicializar t_exec");
		}

		if (minishell->exec->first_cmd)
            free_cmd_list(minishell->exec->first_cmd);

		int i = 0;
		minishell->exec->first_cmd = create_cmd_list(minishell->tokens, minishell->exec->paths, &i);

		if (!minishell->exec->first_cmd)
		{
			printf("Error: creating commands list.\n");
			free(input);
			continue ;
		}
		add_details_to_cmd_list(minishell->exec->first_cmd, minishell->tokens);

		if (execute_commands(minishell) != TRUE)
		{
			free_cmd_list(minishell->exec->first_cmd);
			free_mini(minishell);
			free(input);
			break ;
		}
		free(input);
	}

	free_mini(minishell);
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


