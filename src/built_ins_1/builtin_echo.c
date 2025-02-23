/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/23 12:04:52 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 23:09:49 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 12:32:51 by dasalaza         ###   ########.fr       */
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

int	ft_echo(t_cmd *cmd, t_mini *mini)
{
	int	i;
	int	no_newline;
	char *expanded_arg;

	i = 1;
	no_newline = 0;
	while (cmd->cmd_args[i] && ft_strcmp(cmd->cmd_args[i], "-n") == 0)
	{
		no_newline = 1;
		i ++;
	}
	while (cmd->cmd_args[i])
	{
		expanded_arg = expand_exit_status(mini, cmd->cmd_args[i]);
		if (expanded_arg)
		{
			printf("%s", expanded_arg);
			free(expanded_arg);
		}
		if (cmd->cmd_args[i + 1])
			printf(" ");
		i ++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
