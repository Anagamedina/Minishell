#include "minishell.h"



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
	//new_cmd->redir_list = NULL;
	new_cmd->input_fd = -1;
	new_cmd->output_fd = -1;
	new_cmd->next = NULL;
	return (new_cmd);
}


t_cmd *create_new_command(t_tokens *current_token, char **paths, int cmd_id)
{
	t_cmd *new_cmd;
	char *cmd_path;

	// Inicializar el comando
	new_cmd = init_command();
	if (!new_cmd)
		return (NULL);

	// Guardar el nombre del comando
	new_cmd->cmd = ft_strdup(current_token->str);
	if (!new_cmd->cmd)
	{
		free_command(new_cmd);
		return (NULL);
	}

	// Asignar ID al comando
	new_cmd->cmd_id = cmd_id;

	// Si es un built-in, no necesita más procesamiento
	if (current_token->type_token == BUILTINS)
		return (new_cmd);

	// Si es un comando externo, obtener su ruta
	if (current_token->type_token == CMD_EXTERNAL)
	{
		cmd_path = get_cmd_path(new_cmd->cmd, paths);
		if (!cmd_path)
		{
			fprintf(stderr, "Error: Comando no encontrado: %s\n", new_cmd->cmd);
			free_command(new_cmd);
			return (NULL);
		}

		// Reemplazar el comando con su ruta absoluta
		free(new_cmd->cmd);
		new_cmd->cmd = cmd_path;
	}

	return (new_cmd);
}

//una funcion que coja las paths como parametros para añadirlo en la linked list de comandos
//llamar a Identificar_comandos!
t_list *create_cmd_list(t_list *token_list, char **paths)
{
	t_list *commands_list = NULL;
	t_list *new_node;
	t_cmd *new_cmd;
	t_tokens *token;
	t_list *current = token_list;
	int cmd_id = 1;

	if (!token_list)
		return NULL;

	while (current)
	{
		token = (t_tokens *)current->content;

		// Si el token es un cmd externo o Builtin
		if (token->type_token == BUILTINS || token->type_token == CMD_EXTERNAL)
		{
			new_cmd = create_new_command(token, paths, cmd_id);
			if (!new_cmd)
			{
				fprintf(stderr, "Error: Falló la creación del comando.\n");
				free_cmd_list(commands_list);
				return NULL;
			}

			new_node = ft_lstnew(new_cmd);
			if (!new_node)
			{
				fprintf(stderr, "Error: No se pudo crear el nodo del comando.\n");
				free_command(new_cmd);
				free_cmd_list(commands_list);
				return NULL;
			}

			ft_lstadd_back(&commands_list, new_node);
			cmd_id++;
		}
		current = current->next;
	}

	return commands_list;
}

//pensar si usar t_mini y pasarle la linked list de comandos
int add_details_to_cmd_list(t_list *commands_list, t_list *token_list)
{
	t_list *current = token_list;
	t_list *cmd_node;
	t_cmd *cmd;
	t_tokens *token;

	while (current)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		{
			// Encontrar el nodo correspondiente al comando
			cmd_node = commands_list;
			while (cmd_node)
			{
				cmd = (t_cmd *)cmd_node->content;
				if (strcmp(cmd->cmd, token->str) == 0)
				{
					count_args(current, cmd);
					add_args(&cmd, current);
					// cmd->redir_list = parse_redirections(&current);
					//if (handle_redirections_and_pipes(cmd, current, exec_pipe) == -1)
						//return -1; // Error al manejar redirecciones o pipes
					break;
				}
				cmd_node = cmd_node->next;
			}
			if (!cmd_node)
			{
				// Si no encontraste el comando, puedes decidir cómo manejarlo. Por ejemplo:
				fprintf(stderr, "Error: Comando '%s' no encontrado en la lista de comandos.\n", token->str);
				return -1;
			}
		}
		current = current->next;
	}
	return 0;
}