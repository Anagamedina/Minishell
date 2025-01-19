/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/19 11:21:01 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*input;
	t_mini	*minishell;


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


		// TODO: create in print exec
		char **envp = lst_to_arr(minishell->env);


			minishell->exec = init_exec(minishell->env);
		if (!minishell->exec)
		{
			perror("Error al inicializar t_exec");
			return 1;
		}

		parser_tokens(minishell);
		minishell->exec->first_cmd = create_cmd_list(minishell->token, minishell->exec->paths);
		if (!minishell->exec->first_cmd)
		{
			printf("Error al crear la lista de comandos.\n");
			continue ;
		}
		printf("************************************\n");
		print_list_token_str(minishell->token);
		printf("************************************\n");

		add_details_to_cmd_list(minishell->exec->first_cmd, minishell->token);


		print_list_commands(minishell->exec->first_cmd);
		//execute_commands(minishell);
		execute_commands(minishell);
		//free_cmd_list(minishell->exec->first_cmd);
		 //cases_builtins(minishell);

	}
	return (0);
}
