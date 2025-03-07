/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 17:59:30 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_exit_status(t_mini *mini, char *str)
{
	if (!str || !mini)
		return (NULL);
	if (ft_strcmp(str, "$?") == 0)
		return (ft_itoa(mini->exit_status));
	return (ft_strdup(str));
}

static int	handle_echo_flags(char **args, int *no_newline)
{
	int	i;

	*no_newline = 0;
	i = 1;
	while (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		*no_newline = 1;
		i++;
	}
	return (i);
}

static void	print_echo_arguments(char **args, int start, t_mini *mini)
{
	char	*expanded_arg;
	int		i;

	i = start;
	while (args[i])
	{
		expanded_arg = expand_exit_status(mini, args[i]);
		if (expanded_arg)
			ft_putstr_fd(expanded_arg, 1);
		free(expanded_arg);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
}

int	ft_echo(t_cmd *cmd, t_mini *mini)
{
	int	no_newline;
	int	start_index;

	if (!cmd || !cmd->cmd_args)
		return (1);
	start_index = handle_echo_flags(cmd->cmd_args, &no_newline);
	print_echo_arguments(cmd->cmd_args, start_index, mini);
	if (!no_newline)
		write(1, "\n", 1);
	return (0);
}

/*
int	ft_echo(t_cmd *cmd, t_mini *mini)
{
	char	*expanded_arg;
	int		no_newline;
	int		i;

	if (!cmd || !cmd->cmd_args)
		return (1);
	i = 1;
	no_newline = 0;
	while (cmd->cmd_args[i] && ft_strcmp(cmd->cmd_args[i], "-n") == 0)
	{
		no_newline = 1;
		i++;
	}
	while (cmd->cmd_args[i])
	{
		expanded_arg = expand_exit_status(mini, cmd->cmd_args[i]);
		if (expanded_arg)
			ft_putstr_fd(expanded_arg, 1);
		free(expanded_arg);
		if (cmd->cmd_args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!no_newline)
		write(1, "\n", 1);
	return (0);
}
*/