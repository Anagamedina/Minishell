/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:37:44 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/08 14:52:10 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_input(char *input, t_mini *minishell)
{
	if (!input)
		handle_exit(minishell);
	if (ft_strlen(input) == 0)
	{
		// free(input);
		return (1);
	}
	return (2);
}

int	tokenize_and_validate(t_mini *minishell, char *input)
{
	if (minishell->tokens)
	{
		free_tokens_list(&minishell->tokens);
		minishell->tokens = NULL;	
	}
	minishell->tokens = generate_token_list(input);
	if (!minishell->tokens || !validate_syntax(minishell->tokens) || \
		!validate_and_update_words_positions(minishell))
	{
		free_tokens_list(&minishell->tokens);
		minishell->tokens = NULL;
		free(input);
		return (0);
	}
	update_words_in_tokens(minishell);
	parser_tokens(minishell);
	parse_redir(minishell);
	return (1);
}

int	execute_commands_pipeline(t_mini *minishell)
{
	if (minishell->exec)
		free_exec(minishell->exec);
	minishell->exec = init_exec(minishell->env);
	if (!minishell->exec)
	{
		ft_putendl_fd("Error: command not found", 2);
		return (0);
	}
	if (minishell->exec->first_cmd)
		free_cmd_list(&minishell->exec->first_cmd);
	minishell->exec->first_cmd = create_cmd_list(minishell->tokens, \
			minishell->exec->paths);
	if (!minishell->exec->first_cmd)
	{
		ft_putendl_fd("Command not found", 2);
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

void	miniloop(t_mini *minishell)
{
	char	*input;

	while (1)
	{
		input = read_input(minishell);
		if (!handle_input(input, minishell))
			break ;
		if (!tokenize_and_validate(minishell, input))
		{
			// free(input);
			continue ;
		}
		if (!execute_commands_pipeline(minishell))
			continue ;
		free(input);
	}
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
	setup_signals(PARENT);
	miniloop(minishell);
	last_exit_code = minishell->exit_status;
	free_mini(minishell);
	return (last_exit_code);
}

/*static void	handle_exit(t_mini *minishell)
{
	int	last_exit_code;

	write(1, "exit\n", 5);
	last_exit_code = minishell->exit_status;
	rl_clear_history();
	free_mini(minishell);
	exit(last_exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*input;
	t_mini	*minishell;

	minishell = init_mini_list(envp);
	if (!minishell)
	{
		ft_putendl_fd("Error: init minishell.", 2);
		return (1);
	}
	setup_signals(PARENT);
	while (1)
	{
		input = read_input(minishell);
		// hanlde Ctrl+D eof
		if (!input)
			handle_exit(minishell);
		if (ft_strlen(input) == 0)
			continue ;
		if (minishell->tokens)
			free_tokens_list(&minishell->tokens);
		minishell->tokens = generate_token_list(input);
		if (!minishell->tokens || !validate_syntax(minishell->tokens) || \
		!validate_and_update_words_positions(minishell))
		{
			// free_tokens_list(&minishell->tokens);
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
			// perror("Error: init exec.\n");
			ft_putendl_fd("Error: command not found", 2);
			// free_mini(minishell);
			free(input);
			// exit(1);
			continue ;
		}
		if (minishell->exec->first_cmd)
			free_cmd_list(&minishell->exec->first_cmd);

		minishell->exec->first_cmd = create_cmd_list(minishell->tokens, minishell->exec->paths);
		if (!minishell->exec->first_cmd)
		{
			printf("Command not found\n");
			// print_command_not_found(minishell->exec->first_cmd->content);
			free_cmd_list(&minishell->exec->first_cmd);
			free(input);
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
}*/
