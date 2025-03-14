/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:00:41 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/14 22:12:44 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quotes_line(const char *line)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' && !in_single)
			in_double = !in_double;
		else if (line[i] == '\'' && !in_double)
			in_single = !in_single;
		i++;
	}
	if (in_single || in_double)
		return (FALSE);
	return (TRUE);
}

char	*read_input(t_mini *mini)
{
	char	*line;

	setup_signals(PARENT, mini);
	line = readline("minishell> ");
	if (!line)
	{
		write(1, "exit\n", 5);
		rl_clear_history();
		free_mini(mini);
		exit(0);
	}
	if (*line)
		add_history(line);
	return (line);
}

int	set_token_type(char *str)
{
	if (!str || ft_strlen(str) == 0)
		return (NULL_TYPE);
	if (ft_strcmp(str, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (REDIR_APPEND);
	else if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, ";") == 0)
		return (DELIMITER);
	else
		return (WORD);
}

void	cleanup_input(t_mini *minishell, char *input)
{
	free_tokens_list(&minishell->tokens);
	minishell->tokens = NULL;
	free(input);
}
