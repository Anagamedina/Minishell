/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/05 11:56:22 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void    cases_builtins(t_mini *mini)
{
    t_cmd   *curr_cmd;

    curr_cmd = (t_cmd *)mini->exec->first_cmd->content;

    if (ft_strcmp(curr_cmd->cmd, "echo") == 0)
    {
		ft_echo(curr_cmd);
    }
	else if (ft_strcmp(curr_cmd->cmd, "export") == 0 && \
		curr_cmd->cmd_args[1] == NULL)
	{
		print_export(mini->env);
	}
	else if (ft_strcmp(curr_cmd->cmd, "export") == 0)
	{
		// TODO: gestionar bien la funcion
		init_process_export(curr_cmd, &(mini->env));
	}
	else if (ft_strcmp(curr_cmd->cmd, "unset") == 0)
	{
	}
	else if (ft_strcmp(curr_cmd->cmd, "env") == 0)
	{
		print_env_list(mini->env);
	}
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
*/
