

#include "../../includes/minishell.h"







/*void update_after_pipe_to_builtin_or_external(t_list *tokens_list, t_mini *mini)
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
				cmd_path = get_cmd_path(curr_token->str, mini->exec->paths);
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
}*/



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