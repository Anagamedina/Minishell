/*
int	identify_commands(t_list *tokens_list)
{
	t_list		*current;
	t_tokens	*tokens;

	if (!tokens_list)
		return (FALSE);
	current = tokens_list;
	while (current)
	{
		tokens = (t_tokens *)current->content;
		if (tokens->type_token == WORD)
		{
			update_words_to_builtin(tokens_list);
		}
		current = current->next;
	}
	update_after_pipe_to_builtin(tokens_list);
	return (TRUE);
}*/

/*
static int	is_builtin(char *str)
{
	if (!str)
		return (FALSE);
	if (ft_strcmp(str, "echo") == 0)
		return (TRUE);
	if (ft_strcmp(str, "export") == 0)
		return (TRUE);
	if (ft_strcmp(str, "unset") == 0)
		return (TRUE);
	if (ft_strcmp(str, "env") == 0)
		return (TRUE);
	if (ft_strcmp(str, "cd") == 0)
		return (TRUE);
	if (ft_strcmp(str, "pwd") == 0)
		return (TRUE);
	if (ft_strcmp(str, "exit") == 0)
		return (TRUE);
	return (FALSE);
}
*/


/**
 * free the current node
 * print error  message
 * return NULL
 *
*/

/*
void	check_null_token(t_tokens *token, t_cmd *cmd_list, char *err_message)
{
	if (token == NULL)
	{
		if (err_message)
			printf("Error: %s\n", err_message);
		if (cmd_list)
			free_command_list(cmd_list);
		return (NULL);
	}
}
*/


/*void contar_numero_argumentos_de_comandos(t_list *token_list, t_cmd *cmd)
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



void	agregar_argumentos_a_comando(t_cmd **cmd, t_list *token_list)
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
}*/
/*t_cmd *create_new_command(t_tokens *current_token, char **paths, int cmd_id)
{
	t_cmd 	*new_cmd;
	char 	*cmd_path;

	new_cmd = init_command();
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = ft_strdup(current_token->str);
	if (!new_cmd->cmd)
	{
		free_command(new_cmd);
		return (NULL);
	}
	cmd_path = get_cmd_path(new_cmd->cmd, paths);
	if (!cmd_path)
	{
		free_command(new_cmd);
		return (NULL);
	}
	new_cmd->cmd = cmd_path; // Almacenamos la ruta completa del comando
	new_cmd->cmd_id = cmd_id;
	return (new_cmd);
}*/
