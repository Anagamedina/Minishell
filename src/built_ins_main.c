/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/26 00:50:06 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void    cases_builtins(t_mini *mini)
{
    t_cmd   *current_command;

    current_command = (t_cmd *)mini->exec->first_cmd->content;

    if ((ft_strcmp((char *)current_command->cmd, "echo") == 0))
    {
		ft_echo(current_command);
    }

    /*
    if ((ft_strcmp((char *)current_command->cmd, "export") == 0))
    {
		builtin_export(mini);
    }
    else if (ft_strcmp((char *)current_command->cmd, "cd") == 0)
	{
		printf("enmtra caso cd\n");
		get_current_directory(mini);
	}
	else
		return ;
*/
}
