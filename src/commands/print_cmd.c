/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/03/07 16:15:59 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	print_list_commands(t_list *cmd_list)
{
	t_list	*current;
	t_cmd	*cmd;
	t_list	*redir_node;
	t_redir	*redir;
	int		i;

	current = cmd_list;
	while (current != NULL)
	{
		cmd = (t_cmd *)current->content;
		printf("============================\n");
		printf("Command name: %s\n", cmd->cmd);
		printf("Args:\n");
		i = 0;
		while (cmd->cmd_args && cmd->cmd_args[i] != NULL)
		{
			printf("\targv[%d] = [%s]\n", i, cmd->cmd_args[i]);
			i++;
		}
		printf("Command ID: [%d]\n", cmd->cmd_id);
		printf("Is Builtin: [%d]\n", cmd->is_builtin);
		printf("Is External: [%d]\n", cmd->is_external);
		printf("Input FD: [%d]\n", cmd->input_fd);
		printf("Output FD: [%d]\n", cmd->output_fd);
		printf("Last Command: [%d]\n", cmd->last_cmd);

		// Imprimir redirecciones si existen
		redir_node = cmd->redir_list;
		if (redir_node)
			printf("Redirections:\n");

		while (redir_node)
		{
			redir = (t_redir *)redir_node->content;
			printf("\tType: [%d] ", redir->type);
			if (redir->type == 0)
				printf("(Input Redirection) ");
			else if (redir->type == 1)
				printf("(Output Redirection) ");
			else if (redir->type == 2)
				printf("(Append Redirection) ");
			printf("\n\tFile: [%s]\n", redir->filename);

			redir_node = redir_node->next;
		}
		printf("============================\n\n");
		current = current->next;
	}
}

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
}*/
