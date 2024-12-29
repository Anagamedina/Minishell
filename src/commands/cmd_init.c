#include "../../includes/minishell.h"



/**
 * Inicializa una nueva estructura de comando con valores por defecto (NULL o -1).
 */
t_cmd *init_command(void)
{
	t_cmd *new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->cmd_args = NULL;
	new_cmd->count_args = -1;
	new_cmd->cmd_id = 0;
	new_cmd->input_fd = -1;
	new_cmd->output_fd = -1;
	new_cmd->next = NULL;
	return (new_cmd);
}

/**
 * Crea un nuevo comando a partir del token actual, asignando un id único al comando.
 */
t_cmd *create_new_command(t_tokens *current_token, int i)
{
	t_cmd *new;

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

//una funcion que coja las paths como parametros para añadirlo en la linked list de comandos




/**
 * Recorre la lista de tokens y agrega los comandos a una lista enlazada,
 * asignando identificadores y argumentos a cada uno.
 */
t_list *add_tokens_to_linked_list_commands(t_list *token_list)
{
	t_list *commands_list;
	t_list *new_node;
	t_cmd *new_cmd;
	t_tokens *token;
	t_list *current;
	int cmd_id;

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

			// Objetivo: Para cada comando contar el número de argumentos
			count_args(current, new_cmd);
			add_args(&new_cmd, current);
			ft_lstadd_back(&commands_list, new_node);
			cmd_id++;
		}
		current = current->next;
	}
	return (commands_list);
}