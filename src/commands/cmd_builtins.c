

#include "../../includes/minishell.h"

// Recorre la lista de tokens y actualiza el tipo de token de las palabras que son comandos internos (builtins).
void update_words_to_builtin(t_list *tokens_list)
{
	t_list		*current;
	t_tokens	*curr_token;

	current = tokens_list;
	while (current)
	{
		curr_token = (t_tokens *)current->content;

		if (curr_token->type_token == WORD)
		{
			if (is_builtin_command(curr_token->str))
				curr_token->type_token = BUILTINS;
		}
		current = current->next;
	}
}

void update_words_to_external(t_list *tokens_list, t_mini *mini)
{
	t_list      *current;
	t_tokens    *curr_token;

	current = tokens_list;
	while (current)
	{
		curr_token = (t_tokens *)current->content;

		// Verifica si el token es un comando y si es externo
		if (curr_token->type_token == WORD)
		{
			if (is_cmd_external(mini, curr_token->str))  // Usamos exec_info para verificar
			{
				curr_token->type_token = CMD_EXTERNAL;  // Marca como CMD_EXTERNAL si es externo
			}
		}

		current = current->next;
	}
}

void update_after_pipe_to_builtin_or_external(t_list *tokens_list, t_mini *mini)
{
	t_list		*current;
	int			after_pipe;
	t_tokens	*curr_token;
	char		*cmd_path;

	current = tokens_list;
	after_pipe = 0;
	while (current)
	{
		curr_token = (t_tokens *)current->content;
		if (curr_token->type_token == PIPE)
			after_pipe = 1;
		else if (after_pipe && curr_token->type_token == WORD)
		{
			if (is_builtin_command(curr_token->str))
				curr_token->type_token = BUILTINS;
			else
			{
				cmd_path = get_cmd_path(curr_token->str, mini->exec->paths);  // Usamos exec_info->paths
				if (cmd_path)
				{
					curr_token->type_token = CMD_EXTERNAL;
					free(cmd_path);
				}
			}
			after_pipe = 0;
		}
		current = current->next;
	}
}


// Función principal que actualiza los tokens identificados como comandos internos (builtins) antes y después de los pipes.
void identify_commands(t_list *tokens_list, t_mini *exec_info)
{
	update_words_to_builtin(tokens_list);
	update_words_to_external(tokens_list, exec_info);  // Pasa exec_info aquí
	update_after_pipe_to_builtin_or_external(tokens_list, exec_info);  // Pasa exec_info aquí
}



// Recorre la lista de tokens y actualiza los tokens después de un pipe (|) que son comandos internos (builtins).
/*void update_after_pipe_to_builtin(t_list *tokens_list)
{
	t_list		*current;
	int			after_pipe;
	t_tokens	*curr_token;

	current = tokens_list;
	after_pipe = 0;
	while (current)
	{
		curr_token = (t_tokens *)current->content;
		if (curr_token->type_token == PIPE)
			after_pipe = 1;
		else if (after_pipe && curr_token->type_token == WORD)
		{
			if (is_builtin_command(curr_token->str))
				curr_token->type_token = BUILTINS;
			after_pipe = 0;
		}
		current = current->next;
	}
}*/