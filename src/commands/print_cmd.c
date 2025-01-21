/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/17 22:16:06 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"



/**
 * print the list of commands
*/

void	print_list_commands(t_list *cmd_list)
{
	t_list	*current;
	t_cmd	*cmd;
	int		i;

	current = cmd_list;
	i = 0;
	while (current != NULL)
	{
		cmd = (t_cmd *)current->content;
		printf("----------------------------\n");
		printf("Command name: %s\n", cmd->cmd);
		printf("Args:\n");
		i = 0;
		while (cmd->cmd_args && cmd->cmd_args[i] != NULL)
		{
			printf("\targv[%d] = [%s]\n", i, cmd->cmd_args[i]);
			i ++;
		}
		printf("Command ID: [%d]\n", cmd->cmd_id);
		printf("----------------------------\n");
		current = current->next;
	}
}