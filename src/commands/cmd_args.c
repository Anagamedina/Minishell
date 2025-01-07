#include "minishell.h"


// Cuenta el número de tokens de tipo WORD en la lista
// hasta encontrar un DELIMITER o BUILTIN.
// Pre: token_list apunta a un token de tipo BUILTIN.

/*void count_args(t_list *token_list, t_cmd *cmd)
{
	t_list		*current;
	t_tokens	*token;

	if (!token_list || !cmd)
		return;

	//current = token_list->next;
	current = token_list;
	cmd->count_args = 0;

	while (current)
	{
		token = (t_tokens *)current->content;

		// Detén la cuenta si encuentras otro comando o un delimitador
		if (token->type_token == BUILTINS ||
			token->type_token == CMD_EXTERNAL ||
			token->type_token == DELIMITER ||
			token->type_token == PIPE)
			break;

		// Incrementa si es un argumento válido
		if (token->type_token == WORD)
			cmd->count_args++;

		current = current->next;
	}
}
*/
void count_args(t_list *token_list, t_cmd *cmd)
{
	t_list      *current;
	t_tokens    *token;

	if (!token_list || !cmd)
		return;

	current = token_list; // Comienza desde el primer token
	cmd->count_args = 0;

	// Si el primer token es un comando externo o un built-in, cuenta como un argumento.
	token = (t_tokens *)current->content;
	if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
	{
		cmd->count_args = 1; // El primer comando cuenta como un argumento
		printf("cmd->count_args: %d\n", cmd->count_args);
	}

	current = current->next; // Avanza al siguiente token para contar los argumentos

	// Ahora cuenta los argumentos (tokens de tipo WORD)
	while (current)
	{
		token = (t_tokens *)current->content;

		// Detén la cuenta si encuentras otro comando, un delimitador, o un pipe
		if (token->type_token == BUILTINS ||
			token->type_token == CMD_EXTERNAL ||
			token->type_token == DELIMITER ||
			token->type_token == PIPE)
			break;

		// Incrementa el contador si es un argumento válido
		if (token->type_token == WORD)
			cmd->count_args++;

		current = current->next;
	}
}


void add_args(t_cmd **cmd, t_list *token_list)
{
	t_list      *current;
	t_tokens    *token;
	int         j = 0;

	if (!cmd || (*cmd)->count_args <= 0)
		return;

	// Reserva memoria para cmd_args con un tamaño adecuado
	(*cmd)->cmd_args = ft_calloc((*cmd)->count_args + 1, sizeof(char *));
	if (!(*cmd)->cmd_args)
		return;

	current = token_list;
	// Primero, agrega el comando (que es el primer token)
	token = (t_tokens *)current->content;
	if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
	{
		(*cmd)->cmd_args[j] = ft_strdup(token->str);
		if (!(*cmd)->cmd_args[j])
		{
			perror("Error al duplicar el comando");
			while (--j >= 0)
				free((*cmd)->cmd_args[j]);
			free((*cmd)->cmd_args);
			return;
		}
		j++;
	}

	// Ahora, agrega los argumentos (tokens de tipo WORD)
	current = current->next; // Avanza al siguiente token
	while (current && j < (*cmd)->count_args)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == WORD)
		{
			(*cmd)->cmd_args[j] = ft_strdup(token->str);
			if (!(*cmd)->cmd_args[j])
			{
				perror("Error al duplicar el argumento");
				while (--j >= 0)
					free((*cmd)->cmd_args[j]);
				free((*cmd)->cmd_args);
				return;
			}
			j++;
		}
		current = current->next;
	}

	(*cmd)->cmd_args[j] = NULL; // Asegura que el último índice sea NULL
}