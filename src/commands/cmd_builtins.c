

#include "../../includes/minishell.h"

int	is_builtin_command(const char *str)
{
	return (strcmp(str, ECHO) == 0 || strcmp(str, EXPORT) == 0 || \
		strcmp(str, UNSET) == 0 || strcmp(str, ENV) == 0 || \
		strcmp(str, CD) == 0 || strcmp(str, PWD) == 0 || \
		strcmp(str, EXIT) == 0);
}

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

// Recorre la lista de tokens y actualiza los tokens después de un pipe (|) que son comandos internos (builtins).
void update_after_pipe_to_builtin(t_list *tokens_list)
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
}

// Función principal que actualiza los tokens identificados como comandos internos (builtins) antes y después de los pipes.
void identify_commands(t_list *tokens_list)
{
	update_words_to_builtin(tokens_list);
	update_after_pipe_to_builtin(tokens_list);
}