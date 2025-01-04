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
	new_cmd->cmd_split = NULL;
	new_cmd->count_args = -1;
	new_cmd->cmd_id = 0;
	//new_cmd->redir_list = NULL;
	new_cmd->input_fd = -1;
	new_cmd->output_fd = -1;
	new_cmd->next = NULL;

	return (new_cmd);
}

// Esta función divide el comando en flags y los guarda en cmd_flags
/*void process_flags(t_cmd *cmd, char *cmd_str)
{
	char **cmd_split;

	// Dividir el comando en tokens separados por espacios
	cmd_slit = ft_split(cmd_str, ' ');
	if (!cmd_split)
	{
		perror("Error: ft_split cmd failed");
		return;
	}

	//cmd->cmd_flags = ft_calloc(1, sizeof(char *));
	//if (!cmd->cmd_flags)
	//{
		//perror("Error al asignar memoria para cmd_flags");
		//free(cmd_split);
		//return;
	//}
	cmd->cmd_split = cmd_split;
}*/

/*
static t_cmd *create_new_external_command(t_tokens *token, char **paths, int cmd_id)
{
	t_cmd	*new;
	char	*cmd_path;

	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		perror("Error: malloc failed");
		return (NULL);
	}
	//new->cmd_args = ft_split(token->str, ' ');
	//if (!new->cmd_args)
	//{
		//perror("Error: ft_split failed");
		//return (NULL);
	//}
	//cmd_path = get_cmd_path(new->cmd, paths);
	if (cmd_path == NULL)
		return (handle_cmd_error(new));
	//free(new->cmd_args[0]);
	//new->cmd_args[0] = cmd_path;
	new->cmd = cmd_path;
	new->next = NULL;
	return (new);
}
*/

static t_cmd *create_new_builtin_command(t_tokens *token, int cmd_id)
{
	t_cmd *new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return NULL;

	new_cmd->cmd_id = cmd_id;
	new_cmd->cmd = ft_strdup(token->str);
	if (!new_cmd->cmd)
	{
		free(new_cmd);
		return NULL;
	}
	// TODO: gestionar args no null
	//new_cmd->cmd_args = NULL;
	//new_cmd->redir_list = NULL;
	return (new_cmd);
}

//una funcion que coja las paths como parametros para añadirlo en la linked list de comandos
//llamar a Identificar_comandos!

t_list *create_cmd_list(t_list *token_list, char **paths)
{
	t_list *commands_list = NULL;
	t_list *new_node = NULL;
	t_cmd *new_cmd;
	t_tokens *token;
	t_list *current = token_list;
	int cmd_id = 1;

	if (!token_list)
		return NULL;

	while (current)
	{
		token = (t_tokens *)current->content;
		printf("Procesando token: '%s'\n", token->str);
		printf("Tipo de token: %d\n", token->type_token);

		// Crear nodo según el tipo de comando
		if (token->type_token == CMD_EXTERNAL)
		{
			//new_cmd = create_new_external_command(token, paths, cmd_id);
			new_cmd = create_new_builtin_command(token, cmd_id);
		}
		else if (token->type_token == BUILTINS)
		{
			new_cmd = create_new_builtin_command(token, cmd_id);
		}
		else
		{
			current = current->next;
			continue;
		}

		if (!new_cmd)
		{
			fprintf(stderr, "Error: Falló la creación del comando '%s'.\n", token->str);
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
		current = current->next;
	}
	return commands_list;
}

/*
if (!new_cmd)
{
	fprintf(stderr, "Error: Falló la creación del comando '%s'.\n", token->str);
	free_cmd_list(commands_list);
	return NULL;
}

// Crear nodo de la lista enlazada
new_node = ft_lstnew(new_cmd);
if (!new_node)
{
	fprintf(stderr, "Error: No se pudo crear el nodo del comando.\n");
	free_command(new_cmd);
	free_cmd_list(commands_list);
	return NULL;
}
 */
int add_details_to_cmd_list(t_list *commands_list, t_list *token_list)
{
	t_list *current = token_list;
	t_list *cmd_node;
	t_cmd *cmd;
	t_tokens *token;

	while (current)
	{
		token = (t_tokens *)current->content;
		printf("Procesando token: '%s' de tipo: %d\n", token->str, token->type_token);

		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		{
			cmd_node = commands_list;
			while (cmd_node)
			{
				cmd = (t_cmd *)cmd_node->content;
				printf("Comparando con comando: '%s'\n", cmd->cmd);

				//if (strcmp(cmd->cmd, token->str) == 0)
				if (strcmp(cmd->cmd, token->str) == 0)
				{
					printf("Comando encontrado: '%s'\n", cmd->cmd);
					count_args(current, cmd);
					add_args(&cmd, current);
					break;
				}
				cmd_node = cmd_node->next;
			}
			if (!cmd_node)
			{
				fprintf(stderr, "Error: Comando '%s' no encontrado en la lista de comandos.\n", token->str);
				return -1;
			}
		}
		current = current->next;
	}
	return 0;
}

//pensar si usar t_mini y pasarle la linked list de comandos
/*int add_details_to_cmd_list(t_list *commands_list, t_list *token_list)
{
	t_list *current = token_list;
	t_list *cmd_node;
	t_cmd *cmd;
	t_tokens *token;

	while (current)
	{
		token = (t_tokens *)current->content;
		printf("Procesando token: '%s' de tipo: %d\n", token->str, token->type_token);

		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		{
			cmd_node = commands_list;
			while (cmd_node)
			{
				cmd = (t_cmd *)cmd_node->content;
				printf("Comparando con comando: '%s'\n", cmd->cmd);

				//if (strcmp(cmd->cmd, token->str) == 0)
				if (strcmp(cmd->cmd_args[0], token->str) == 0)
				{
					printf("Comando encontrado: '%s'\n", cmd->cmd);
					count_args(current, cmd);
					add_args(&cmd, current);
					break;
				}
				cmd_node = cmd_node->next;
			}
			if (!cmd_node)
			{
				fprintf(stderr, "Error: Comando '%s' no encontrado en la lista de comandos.\n", token->str);
				return -1;
			}
		}
		current = current->next;
	}
	return 0;
}
*/


/*t_cmd *create_new_command(t_tokens *current_token, char **paths, int cmd_id)
{
	t_cmd *new_cmd;
	char *cmd_path;

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
	new_cmd->cmd_id = cmd_id;
	if (current_token->type_token == BUILTINS)
		return (new_cmd);
	if (current_token->type_token == CMD_EXTERNAL)
	{
		process_flags(new_cmd,new_cmd->cmd);
		cmd_path = get_cmd_path(new_cmd->cmd, paths);
		if (!cmd_path)
		{
			fprintf(stderr, "Error: Comando externo '%s' no encontrado en PATH.\n", new_cmd->cmd);
			free_command(new_cmd);
			return (NULL);
		}
		free(new_cmd->cmd);
		new_cmd->cmd = cmd_path;
	}

	return (new_cmd);
}*/