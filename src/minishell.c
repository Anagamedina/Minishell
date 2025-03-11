/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:37:44 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/11 10:49:42 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokenize_and_validate(t_mini *minishell, char *input)
{
	if (minishell->tokens)
	{
		free_tokens_list(&minishell->tokens);
		minishell->tokens = NULL;
	}
	minishell->tokens = generate_token_list(input);
	if (!minishell->tokens || !validate_syntax(minishell->tokens, minishell) || \
		!validate_and_update_words_positions(minishell))
	{
		free_tokens_list(&minishell->tokens);
		minishell->tokens = NULL;
		return (0);
	}
	update_words_in_tokens(minishell);
	parser_tokens(minishell);
	parse_redir(minishell);
	return (1);
}

static int	execute_commands_pipeline(t_mini *minishell)
{
	if (minishell->exec)
		free_exec(minishell->exec);
	minishell->exec = init_exec(minishell->env);
	if (!minishell->exec)
		return (0);
	if (minishell->exec->first_cmd)
		free_cmd_list(&minishell->exec->first_cmd);
	minishell->exec->first_cmd = create_cmd_list(minishell->tokens, \
			minishell->exec->paths);
	if (!minishell->exec->first_cmd)
	{
		minishell->exit_status = 127;
		ft_putendl_fd("Command not found", 2);
		free_exec(minishell->exec);
		minishell->exec = NULL;
		return (0);
	}
	add_details_to_cmd_list(minishell->exec->first_cmd, minishell->tokens);
	if (execute_commands(minishell) != TRUE)
	{
		free_cmd_list(&minishell->exec->first_cmd);
		free_mini(minishell);
		exit(1);
	}
	return (1);
}

static int	validate_input(char *input, t_mini *minishell)
{
	if (!check_quotes_line(input))
	{
		printf("Error: unclosed quotes detected.\n");
		minishell->exit_status = 1;
		return (0);
	}
	if (ft_strlen(input) == 0)
		return (0);
	return (1);
}

void	miniloop(t_mini *minishell)
{
	char	*input;

	while (1)
	{
		input = read_input(minishell);
		if (!input)
			continue ;
		if (!validate_input(input, minishell))
		{
			free(input);
			continue ;
		}
		if (!tokenize_and_validate(minishell, input))
		{
			free(input);
			continue ;
		}
		setup_signals(CHILD); 
		if (!execute_commands_pipeline(minishell))
		{
			free_tokens_list(&minishell->tokens);
			minishell->tokens = NULL;
			free(input);
			continue ;
		}
		free_tokens_list(&minishell->tokens);
		minishell->tokens = NULL;
		free(input);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*minishell;
	int		last_exit_code;

	(void) argc;
	(void) argv;

	minishell = init_mini_list(envp);
	if (!minishell)
		return (ft_putendl_fd("Error: init minishell.", 2), 1);
	miniloop(minishell);
	last_exit_code = minishell->exit_status;
	free_mini(minishell);
	return (last_exit_code);
}
