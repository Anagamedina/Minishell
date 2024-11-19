//
// Created by daruuu on 11/19/24.
//
#include "../../includes/minishell.h"
/*
 * free content of cmd node
 * cmd->cmd
 * cmd->cmd_args
 */
void	free_command(t_cmd *cmd)
{
	if (cmd->cmd)
		free(cmd->cmd);
//	if (cmd->cmd_args)
//		free_split(cmd->cmd_args);
}

/*
 * detectar si el token actual es un tipo de operador de tipo enum
 */

int	is_type_of_operator(t_tokens *token)
{
	return (token->type_token == PIPE || \
		token->type_token == REDIR_INPUT || \
		token->type_token == REDIR_OUTPUT || \
		token->type_token == CONCAT_OUTPUT);
}

/*
 * init struct commands and filling
 * with data of (t_env struct)
*/

t_cmd	*init_command_list(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
//		free(new_cmd);
		return (NULL);
	}
	new_cmd->cmd = NULL;
	new_cmd->cmd_args = NULL;
	new_cmd->cmd_id = 0;
	new_cmd->input_fd = -1;
	new_cmd->output_fd = -1;
	new_cmd->flag_input_redir = 0;
	new_cmd->flag_output_redir = 0;
	new_cmd->next = NULL;
	return (new_cmd);
}

/*
 * create a function to introduce each t_env in the list
 * like a command .
 * example:
 * new_cmd->cmd_args[0] = "cd";
 * new_cmd->cmd_args[1] = "/bin";
 * new_cmd->cmd_args[2] = NULL;
 * minishel >> "ls -l | grep minishell > output.txt"
 * cmd = "ls"
 * cmd_args =
 * 			{"ls", "-l", NULL}
 * cmd = "grep"
 * cmd_args =
 * 			{"grep", "minishell", NULL}
 */

//**********MAIN FUNCTION***************/
t_cmd	*add_commands_to_list(t_tokens *tokens)
{
	t_cmd	*new_cmd;
	t_cmd	*cmd_list;
	t_cmd	*tail;

	cmd_list = NULL;
	tail = NULL;
	while (tokens != NULL)
	{
		new_cmd = init_command_list();
		if (!new_cmd)
			return (NULL);
		new_cmd->cmd = ft_strdup(tokens->str);
		new_cmd->cmd_args[0] = ft_strdup(tokens->str);
//		new_cmd->cmd_args = ft_split(, ' ');
//		add a function to (how add the args of each command) TODO: (daruny)
		if (!new_cmd->cmd || !new_cmd->cmd_args)
		{
			free_command(new_cmd);
			return (NULL);
		}
		//	add to linked list
		if (!cmd_list)
			cmd_list = new_cmd;	//inizialite empty linkedlist
		else
			tail->next = new_cmd;	//agregar al final de la lista
		tail = new_cmd;	//actualizar el ultimo nodo
		if ((tokens = tokens->next))	// &&
		tokens = tokens->next;
	}
	return (new_cmd);
}

/*
 * print the list of commands
 */
void	print_list_commands(t_list *cmd_list)
{
	t_list	*current;
	t_cmd	*cmd;

	current = cmd_list;
	while (current != NULL)
	{
		cmd = (t_cmd *)current->content;
		printf("Command name: %s\n", cmd->cmd);
		printf("args: \n\targv[0]=[%s]\n\targv[1]=[%s]\n\targv[2]=[%s]\n\targv[3]=[%s]\n"\
		, cmd->cmd_args[0]\
		, cmd->cmd_args[1]\
		, cmd->cmd_args[2]\
		, cmd->cmd_args[3]);
		printf("Command ID: [%d]\n", cmd->cmd_id);
		printf("input_fd: %d\n", cmd->input_fd);
		printf("output_fd: %d\n", cmd->output_fd);
		printf("flag_input_redir: %d\n", cmd->flag_input_redir);
		printf("flag_output_redir: %d\n", cmd->flag_output_redir);
		current = current->next;
	}
}