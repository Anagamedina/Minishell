/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 21:09:54 by dasalaza         ###   ########.fr       */
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
	char *tmp;

	if (!str || !mini)
		return (NULL);
	tmp = NULL;
	if (ft_strchr(str, '$'))
	{
		if (ft_strcmp(str, "$?") == 0)
		{
			tmp = ft_itoa(mini->exit_status);
			if (!tmp)
				return (ft_strdup(""));
			return (tmp);
		}
	}
	return (ft_strdup(str));
}

int	ft_echo(t_cmd *cmd, t_mini* mini)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	while (cmd->cmd_args[i] && ft_strcmp(cmd->cmd_args[i], "-n") == 0)
	{
		no_newline = 1;
		i ++;
	}
	while (cmd->cmd_args[i])
	{
		if (cmd->cmd_args[i][0] == '$' && ft_strcmp(cmd->cmd_args[i], "$?") == 0)
        {
            char *tmp = expand_exit_status(mini, cmd->cmd_args[i]);
            if (tmp)
            {
                printf("[%s]", tmp);
                free(tmp);
            }
        }
		else
		{
            printf("%s", cmd->cmd_args[i]);
            if (cmd->cmd_args[i + 1])
                printf(" ");
		}
		i ++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
