#include "minishell.h"

int	is_builtin_command(const char *cmd)
{
	return (strcmp(cmd, ECHO) == 0 || strcmp(cmd, EXPORT) == 0 || \
		strcmp(cmd, UNSET) == 0 || strcmp(cmd, ENV) == 0 || \
		strcmp(cmd, CD) == 0 || strcmp(cmd, PWD) == 0 || \
		strcmp(cmd, EXIT) == 0);
}


// Cuenta el número de tokens de tipo WORD en la lista
// hasta encontrar un DELIMITER o BUILTIN.
// Pre: token_list apunta a un token de tipo BUILTIN.
void count_args(t_list *token_list, t_cmd *cmd)
{
	t_list		*current;
	t_tokens	*token;

	if (!token_list || !cmd)
		return;

	current = token_list;
	token = (t_tokens *)current->content;
	if (token->type_token != BUILTINS && token->type_token != WORD)
	{
		cmd->count_args = 0;
		return;
	}
	cmd->count_args = 0;
	//current = token_list->next;
	//current = token_list;
	//token = (t_tokens *)current->content;
	while(current)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == DELIMITER)
			break;
		if (token->type_token == WORD)
		{
			cmd->count_args++;
		}
		current = current->next;
	}
}

// Reserva memoria y rellena cmd->cmd_args con los tokens de tipo WORD de la lista.
void add_args(t_cmd **cmd, t_list *token_list)
{
	t_list 		*current;
	t_tokens 	*token;
	int 		j = 0;

	if (!cmd || (*cmd)->count_args <= 0)
		return;
	(*cmd)->cmd_args = ft_calloc((*cmd)->count_args + 1, sizeof(char *));
	if (!(*cmd)->cmd_args)
		return;

	current = token_list;
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
				(*cmd)->cmd_args = NULL;
				return;
			}
			j++;
		}
		current = current->next;
	}
	(*cmd)->cmd_args[j] = NULL;
}


/*void handle_cmd(t_list *token_list, t_cmd **cmd, char **paths, int cmd_id)
{
    t_tokens *token = (t_tokens *)token_list->content;

    // Comprobar si el comando es un *builtin* o un comando externo
    if (is_builtin(token))  // Si es un builtin
    {
        (*cmd)->is_builtin = 1;
    }
    else  // Si es un comando externo
    {
        (*cmd)->is_builtin = 0;
    }

    // Contar y añadir los argumentos
    count_args(token_list, *cmd);
    add_args(cmd, token_list);

    // Para comandos externos, buscamos la ruta
    if (!(*cmd)->is_builtin)
    {
        (*cmd)->cmd_path = get_cmd_path((*cmd)->cmd, paths);
    }

    (*cmd)->cmd_id = cmd_id;
}*/