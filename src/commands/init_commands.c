//
// Created by daruuu on 11/19/24.
//
#include "../../includes/minishell.h"

/**
 * Verify if a token is an operator (|, <, > o >>).
 * this function categorize the tokens
*/

int	is_type_of_operator(t_tokens *token)
{
	return (token->type_token == PIPE || \
		token->type_token == REDIR_INPUT || \
		token->type_token == REDIR_OUTPUT || \
		token->type_token == CONCAT_OUTPUT);
}

/**
 * init struct commands with NULL
*/

t_cmd	*init_command(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
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

/**
 * print the list of commands
*/

void	print_list_commands(t_list *cmd_list)
{
	t_list	*current;
	t_cmd	*cmd;
//	int		i;

	current = cmd_list;
//	i = 0;
	while (current != NULL)
	{
		cmd = (t_cmd *)current->content;
		printf("----------------------------\n");
		printf("Command name: %s\n", cmd->cmd);
/*
		printf("Args:\n");
		while (cmd->cmd_args && cmd->cmd_args[i] != NULL)
		{
			printf("\targv[%d] = [%s]\n", i, cmd->cmd_args[i]);
			i ++;
		}
*/
		printf("Command ID: [%d]\n", cmd->cmd_id);
		printf("----------------------------\n");
		current = current->next;
	}
}

/**
 * create_new_command - Initializes a t_cmd.
 * cmd_token string
 * cmd_id to the given ID.
 * arguments are not handled here.
 * @example
 * t_cmd	*command = create_new_command(token, 1);
*/
//**********MAIN FUNCTION***************/
t_cmd	*create_new_command(t_tokens *current_token, int i)
{
	t_cmd	*new;

	new = init_command();
	if (!new)
	{
		perror("Error: malloc failed creating new_command");
		free(new);
		return (NULL);
	}
	new->cmd = ft_strdup(current_token->str);
	if (!new->cmd)
	{
		free_command(new);
		return (NULL);
	}
	new->cmd_id = i;
	return (new);
}

//	********** MAIN FUNCTION ***************/
/**
 * Converts a list of tokens into a list of commands. or NULL if an error occurs.
 *
 * This function processes a linked list of tokens, identifies valid commands
 * (BUILT_INS), and creates a new linked list of t_cmd structures representing
 * these commands. Each command is initialized with its corresponding token data
 * and a unique command ID.
 *
 * If an error occurs during token processing, command creation, or node creation
 * the function cleans up allocated memory and returns NULL.
 *
 * Parameters:
 * @token_list: The linked list of tokens to process.
 *
 * @return:
 * A linked list of t_cmd structures representing the commands,
 * or NULL if an error occurs.
*/

t_list	*add_tokens_to_linked_list_commands(t_list *token_list)
{
	t_list		*commands_list;
	t_list		*new_node;
	t_cmd		*new_cmd;
	t_tokens	*token;
	t_list		*current;
	t_list		*tmp_current;
	int			cmd_id;

	commands_list = NULL;
	cmd_id = 1;
	current = token_list;
	while (current)
	{
		token = (t_tokens *)current->content;
		if (!error_empty_token(token, commands_list))
			return (NULL);
		if (token->type_token == BUILTINS)
		{
			new_cmd = create_new_command(token, cmd_id);
			if (!error_cmd_creation(new_cmd, commands_list))
				return (NULL);
			new_node = ft_lstnew(new_cmd);
			if (!error_node_creation(new_node, new_cmd, commands_list))
				return (NULL);

			// Objetivo: Para cada comando contar el numero de argumento
			int numero_argumentos = 0;
			tmp_current = current->next; // inicio de los argumentos.
			// Nota: Falta la condicion de parar cuando encuentre un token diferente a word.
			while(tmp_current)
			{
				token = (t_tokens *)tmp_current->content;
				if (token->type_token == WORD) {
					numero_argumentos++;
				}
				tmp_current = tmp_current->next;
			}
			new_cmd->cmd_args = malloc(sizeof(char *) * (numero_argumentos + 1));
			tmp_current = current->next;
			int j = 0;
			while (j < numero_argumentos)
			{
				token = (t_tokens *)tmp_current->content;
				new_cmd->cmd_args[j] = token->str;
				tmp_current = tmp_current->next;
				j++;
			}
			printf("Numero argumentos: %d\n", numero_argumentos);
			j = 0;
			while (j < numero_argumentos)
			{
				printf("arg[%d] = [%s]\n", j, new_cmd->cmd_args[j]);
				j++;
			}
			ft_lstadd_back(&commands_list, new_node);
			cmd_id++;
		}
		current = current->next;
	}
	return (commands_list);
}
