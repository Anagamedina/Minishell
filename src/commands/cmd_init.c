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

t_cmd *create_new_command(t_tokens *token, int cmd_id)
{
	t_cmd *new_cmd = init_command();

	if (!new_cmd)
		return NULL;

	new_cmd->cmd_id = cmd_id;
	new_cmd->cmd = ft_strdup(token->str);
	if (!new_cmd->cmd)
	{
		free_command(new_cmd);
		return NULL;
	}

	if (token->type_token == BUILTINS)
	{
		new_cmd->is_builtin = 1; // Marcar como builtin
	}
	else
	{
		new_cmd->is_builtin = 0; // Es un comando externo
	}

	return new_cmd;
}


t_list *create_cmd_list(t_list *token_list)
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
		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		{
			new_cmd = create_new_command(token, cmd_id);
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