/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:37:44 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 18:37:44 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:58:03 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 18:13:53 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*input;
	t_mini	*minishell;
	int		last_exit_code;

	minishell = init_mini_list(envp);
	if (!minishell)
	{
		perror("Error: init minishell.\n");
		return (1);
	}
	setup_signals(PARENT);
	while (1)
	{
		input = read_input(minishell);
		if (!input)
		{
			write(1, "exit\n", 5);
			last_exit_code = minishell->exit_status;
			rl_clear_history();
			free_mini(minishell);
			exit(last_exit_code);
		}
		if (ft_strlen(input) == 0)
		{
			continue;
		}
		if (minishell->tokens)
			free_tokens_list(&minishell->tokens);
		minishell->tokens = generate_token_list(input);
		if (!minishell->tokens || !validate_syntax(minishell->tokens) ||
		!validate_and_update_words_positions(minishell))
		{
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
			free_mini(minishell);
			exit(1);
		}
		if (minishell->exec->first_cmd)
			free_cmd_list(&minishell->exec->first_cmd);

		minishell->exec->first_cmd = create_cmd_list(minishell->tokens, minishell->exec->paths);
		if (!minishell->exec->first_cmd)
		{
			printf("bash: command not found\n");
			free_cmd_list(&minishell->exec->first_cmd);
			continue ;
		}
		add_details_to_cmd_list(minishell->exec->first_cmd, minishell->tokens);
		if (execute_commands(minishell) != TRUE)
		{
			free_cmd_list(&minishell->exec->first_cmd);
			free_mini(minishell);
			free(input);
			exit(1);
		}
		free(input);
	}
	free_mini(minishell);
	return (0);
}
