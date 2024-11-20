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
	int i;

	if (cmd->cmd)
		free(cmd->cmd);
	i = 0;
	while (cmd->cmd_args && cmd->cmd_args[i] != NULL)
	{
		free(cmd->cmd_args[i]);
		i ++;
	}
	free(cmd->cmd_args);
}

/*
 * Función: Verifica si un token es un operador (|, <, > o >>).
 * Comentarios:
 * Es una función compacta y eficiente para categorizar tokens.
 * Es útil para dividir comandos en base a operadores
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
t_cmd	*init_command(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
	{
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
 * print the list of commands
 */
void	print_list_commands(t_list *cmd_list)
{
	t_list	*current;
	t_cmd	*cmd;
	int 	i;

	current = cmd_list;
	i = 0;
	while (current != NULL)
	{
		cmd = (t_cmd *)current->content;
		printf("Command name: %s\n", cmd->cmd);
		printf("Args:\n");
		while (cmd->cmd_args && cmd->cmd_args[i] != NULL)
		{
			printf("\targv[%d] = [%s]\n", i, cmd->cmd_args[i]);
			i ++;
		}
		printf("Command ID: [%d]\n", cmd->cmd_id);
		printf("input_fd: %d\n", cmd->input_fd);
		printf("output_fd: %d\n", cmd->output_fd);
		printf("flag_input_redir: %d\n", cmd->flag_input_redir);
		printf("flag_output_redir: %d\n", cmd->flag_output_redir);
		current = current->next;
	}
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

// call this function in generate_token_list(token_list.c)
//	echo -n abcd

//  CREAR NODOS DE CADA COMANDO
//	str  =  "ls -l"
// new->cmd_args[0]  = "ls",
// new->cmd_args[1]  = "-l".

//**********MAIN FUNCTION***************/
t_cmd	*create_new_command(t_tokens *current_token, int i)
{
	t_cmd	*new;
	int 	j;

	new = init_command();
	if (!new)
	{
		perror("Error: malloc failed creating new_command");
		return (NULL);
	}
	new->cmd = ft_strdup(current_token->str);
	if (!new->cmd)
	{
		free_command(new);
		return (NULL);
	}
	new->cmd_args = malloc(sizeof(char *) * 10); // ??Ajusta el tamaño si es necesario
	if (!new->cmd_args)
	{
		perror("Error: malloc failed for cmd_args");
		free_command(new);
		return (NULL);
	}
	new->cmd_args[0] = current_token->str;
	j = 1;
	while (current_token->next && current_token->next->type_token == WORD)
	{
		current_token = current_token->next;
		new->cmd_args[j] = ft_strdup(current_token->next->str);
		if (!new->cmd_args[j])
		{
			free_command(new);
			return (NULL);
		}
		j ++;
	}
	new->cmd_args[j] = NULL;
	new->cmd_id = i;
	new->next = NULL;
	return (new);
}

//**********MAIN FUNCTION***************/
/*
 * Convierte una lista de tokens en una lista de comandos.
 * TODO: (daurny) finish this function
 */

void	add_tokens_to_linked_list_commands(t_list *token_list, t_cmd **cmd_list)
{
	t_list		*current;
	t_tokens	*token_curr;
	t_cmd		*new_cmd;
	t_cmd		*last_cmd;

	if (!token_list)
	{
		printf("error with token_list(init_command()\n");
		return ;
	}
	current = token_list;
	while (current != NULL)
	{
		token_curr = (t_tokens *)current->content;
		if (token_curr->type_token == BUILT_INS && token_curr->next->type_token == WORD)
		{
			new_cmd = create_new_command( token_curr, 0);
			if (!new_cmd)
			{
				printf("Error: failed to create command\n");
				return;
			}
			// Agregar a la lista de comandos
			if (!(*cmd_list))
				*cmd_list = new_cmd; // Primer comando
			else
				last_cmd->next = new_cmd; // Conectar al último comando
			last_cmd = new_cmd; // Actualizar último comando
		}
		if (token_curr->type_token == PIPE)
		{
			// Aquí podrías inicializar pipes entre comandos
			printf("Found PIPE token\n");
		}
		current = current->next;
	}
}