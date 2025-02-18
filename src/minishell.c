/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:59:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/18 10:20:21 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	/*
	if (!envp || !*envp)
	{
		write(2, "Warning: No environment variables found. Initializing default env.", 65);
		// write(2, "\n", 1);
		printf("\n");
		char *default_env[] = {
			"PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin",
			"HOME=/home/user",
			"SHLVL=1",
			"OLDPWD=",
			NULL
		};
		envp = default_env;
	}
	*/

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
		// free(minishell);
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
		// handle_signal_ctrl_c(SIGINT);
		if ((ft_strcmp(input, "") == 0))
		{
			free(input);
			continue ;
		}
		/*TOKENS
		echo $DISPLAY $USERNAME "123" $HOME 'abc' '$HOME'
		echo $DISPLAY $USERNAME "123" $HOME 'abc' $SHELL """abcd""" $123456 incomplete$HOMEabc $'tab\there'
		echo $'hello\t' abcde is a te\\nst in minishell
		*/
		if (minishell->tokens)
			free_tokens(minishell->tokens);
		minishell->tokens = generate_token_list(input);
		if (!minishell->tokens)
		{
			perror("Error al generar la lista de tokens.\n");
			free(input);
			continue ;
		}
		update_words_in_tokens(minishell);
		parser_tokens(minishell);
		/*if(parse_redir(minishell) == FALSE)
		{
			printf("Error al parsear las redirecciones.\n");
			free(input);
			continue ;
		}*/

		//	INIT EXEC
		if (minishell->exec)
			free_exec(minishell->exec);
		minishell->exec = init_exec(minishell->env);
		if (!minishell->exec)
		{
			perror("Error: init exec.\n");
			free(input);
			break ;
			// return (1);
		}
		//	INIT EXEC FIRST CMD
		if (minishell->exec->first_cmd)
            free_cmd_list(minishell->exec->first_cmd);
		minishell->exec->first_cmd = create_cmd_list(minishell->tokens, minishell->exec->paths);
		if (!minishell->exec->first_cmd)
		{
			printf("Error: creating commands list.\n");
			free(input);
			continue ;
		}

		//	ADD ARGUMENTS TO CMDs
		add_details_to_cmd_list(minishell->exec->first_cmd, minishell->tokens);

		// print_list_commands(minishell->exec->first_cmd);

		//	EXECUTE COMMANDS
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
