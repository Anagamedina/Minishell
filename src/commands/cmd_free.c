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