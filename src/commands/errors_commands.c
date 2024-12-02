//
// Created by daruuu on 11/22/24.
//
#include "../../includes/minishell.h"

/**
 * @param cmd free content of cmd node
*/

void	free_command(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->cmd_args)
	{
		while (cmd->cmd_args[i] != NULL)
		{
			free(cmd->cmd_args[i]);
			i ++;
		}
		free(cmd->cmd_args);
	}
}

/**
 * @param cmd_list free all commands in the list
*/

void	free_command_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = tmp->next;
		free_command(cmd_list);
	}
}

/**
 * free the current node
 * print error  message
 * return NULL
 *
*/

/*
void	check_null_token(t_tokens *token, t_cmd *cmd_list, char *err_message)
{
	if (token == NULL)
	{
		if (err_message)
			printf("Error: %s\n", err_message);
		if (cmd_list)
			free_command_list(cmd_list);
		return (NULL);
	}
}
*/

int	error_empty_token(t_tokens *token, t_list *cmd_list)
{
	if (!token)
	{
		printf("Error: empty token\n");
		free_command_list((t_cmd *) cmd_list);
		return (FALSE);
	}
	return (TRUE);
}


int	error_cmd_creation(t_cmd *cmd, t_list *cmd_list)
{
	if (!cmd)
	{
		printf("Error: can't create command.\n");
		free_command_list((t_cmd *) cmd_list);
		return (FALSE);
	}
	return (TRUE);
}

int	error_node_creation(t_list *node, t_cmd *cmd, t_list *cmd_list)
{
	if (!node)
	{
		printf("Error: can't create command.\n");
		free_command(cmd);
		free_command_list((t_cmd *) cmd_list);
		return (FALSE);
	}
	return (TRUE);
}
