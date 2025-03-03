/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:58:03 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/03 13:58:07 by dasalaza         ###   ########.fr       */
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
		return (1);
	}
	setup_signals(PARENT);
	while (1)
	{
		input = read_input();
		if (!input) // ✅ Detecta `Ctrl+D`
		{
			write(1, "exit\n", 5);
			free_mini(minishell);
			rl_clear_history();
			exit(0);
		}
		if (ft_strlen(input) == 0) // ✅ Línea vacía
		{
			free(input);
			continue;
		}

		if (minishell->tokens)
			free_tokens(minishell->tokens);
		minishell->tokens = generate_token_list(input);
		if (!minishell->tokens || !validate_syntax(minishell->tokens) ||
		!validate_and_update_words_positions(minishell))
		{
			free(input);
			continue;
		}
		update_words_in_tokens(minishell);
		parser_tokens(minishell);
		parse_redir(minishell);
		if (minishell->exec)
			free_exec(minishell->exec);
		minishell->exec = init_exec(minishell->env);
		if (!minishell->exec)
		{
			perror("Error: init exec.\n");
			free(input);
			free_mini(minishell); // ✅ Libera estructuras antes de salir
			exit(1);
			// break ;
		}
		if (minishell->exec->first_cmd)
			free_cmd_list(minishell->exec->first_cmd);
		minishell->exec->first_cmd = create_cmd_list(minishell->tokens, minishell->exec->paths);
		if (!minishell->exec->first_cmd)
		{
			printf("bash: command not found\n");
			free(input);
			continue ;
		}
		add_details_to_cmd_list(minishell->exec->first_cmd, minishell->tokens);
		if (execute_commands(minishell) != TRUE)
		{
			free_cmd_list(minishell->exec->first_cmd);
			free_mini(minishell);
			free(input);
			// break;
			exit(1);
		}
		free(input);
	}
	free_mini(minishell);
	return (0);
}



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

