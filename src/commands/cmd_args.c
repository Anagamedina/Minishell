#include "../../includes/minishell.h"


// Cuenta el número de tokens de tipo WORD en la lista
// hasta encontrar un DELIMITER o BUILTIN.
// Pre: token_list apunta a un token de tipo BUILTIN.
void count_args(t_list *token_list, t_cmd *cmd)
{
	t_list		*current;
	t_tokens	*token;

	cmd->count_args = 0;
	current = token_list->next;
	token = (t_tokens *)current->content;
	while(current && token->type_token != DELIMITER && token->type_token != BUILTINS)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == WORD) {
			cmd->count_args = cmd->count_args + 1;
		}
		current = current->next;
	}
}

// Reserva memoria y rellena cmd->cmd_args con los tokens de tipo WORD de la lista.
void add_args(t_cmd **cmd, t_list *token_list)
{
	t_list		*current;
	t_tokens	*token;

	(*cmd)->cmd_args = malloc(sizeof(char *) * ((*cmd)->count_args + 1));
	if (!(*cmd)->cmd_args)
		return ;
	current = token_list->next;
	int j = 0;
	while (j < (*cmd)->count_args && current)
	{
		token = (t_tokens *)current->content;
		// Crea una copia del string
		(*cmd)->cmd_args[j] = ft_strdup(token->str);
		if (!(*cmd)->cmd_args[j])
		{
			while (--j >= 0)
				free((*cmd)->cmd_args[j]);
			free((*cmd)->cmd_args);
			(*cmd)->cmd_args = NULL;
			return ;
		}
		current = current->next;
		j++;
	}
	(*cmd)->cmd_args[j] = NULL;
}