/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/30 12:13:35 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Init a new struct with default values(NULL o -1).
 */

t_cmd	*init_command(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->cmd_args = NULL;
	new_cmd->count_args = -1;
	new_cmd->cmd_id = 0;
	new_cmd->is_builtin = -1;
	new_cmd->is_external = -1;
	new_cmd->last_cmd = 0;
	new_cmd->input_fd = -1;
	new_cmd->output_fd = -1;
	new_cmd->redir_list = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_cmd	*create_new_command(t_tokens *token, char **paths)
{
	t_cmd	*new_cmd;

	if (!token || !token->str)
		return (NULL);

	new_cmd = init_command();
	if (!new_cmd)
	{
		fprintf(stderr, "Error: No se pudo inicializar el comando\n");
		return (NULL);
	}

	new_cmd->cmd = ft_strdup(token->str);
	if (!new_cmd->cmd)
	{
		free_command(new_cmd);
		return (NULL);
	}
	if (token->type_token == BUILTINS)
		new_cmd->is_builtin = 1;
	else if (token->type_token == CMD_EXTERNAL)
	{
		new_cmd->is_external = 1; // Marcar como comando externo

		// Resolver la ruta del comando
		new_cmd->cmd_path = get_cmd_path(token, paths);
		if (!new_cmd->cmd_path)
		{
			fprintf(stderr, "Error: '%s', paths not found\n", token->str);
			free_command(new_cmd);
			return (NULL);
		}
	}
	return (new_cmd);
}

static t_cmd	*handle_new_command(t_tokens *token, char **paths, t_list *cmd_list, int *cmd_id)
{
	t_cmd	*new_cmd;

	new_cmd = create_new_command(token, paths);
	if (!new_cmd)
	{
		fprintf(stderr, "Error: creating command: [%s].\n", token->str);
		free_cmd_list(cmd_list);
		return (NULL);
	}
	new_cmd->cmd_id = (*cmd_id)++;
	new_cmd->last_cmd = 0;
	return (new_cmd);
}

t_list	*create_cmd_list(t_list *token_list, char **paths, int *cmd_id)
{
	t_list		*commands_list;
	t_list		*new_node;
	t_tokens	*token;
	t_list		*current;
	t_cmd		*new_cmd;

	if (!token_list)
		return (NULL);
	commands_list = NULL;
	current = token_list;
	while (current)
	{
		token = (t_tokens *)current->content;
		if (token->type_token != CMD_EXTERNAL && token->type_token != BUILTINS)
		{
			current = current->next;
			continue ;
		}
		new_cmd = handle_new_command(token, paths, commands_list, cmd_id);
		if (!new_cmd)
			return (NULL);
		new_cmd->last_cmd = (current->next == NULL);
		new_node = ft_lstnew(new_cmd);
		if (!new_node)
		{
			fprintf(stderr, "Error: No se pudo crear el nodo del comando.\n");
			// free_command(new_cmd);
			// free_cmd_list(commands_list);
			// free(new_node);
			return (NULL);
		}
		ft_lstadd_back(&commands_list, new_node);
		current = current->next;
	}
	return (commands_list);
}

/*
 * ORIGINAL
t_list	*create_cmd_list(t_list *token_list, char **paths)
{
	t_list		*commands_list = NULL;
	t_list		*new_node = NULL;
	t_cmd		*new_cmd;
	t_tokens	*token;
	t_list		*current = token_list;
	int			cmd_id;

	if (!token_list)
		return NULL;

	cmd_id = 0;
	while (current != NULL)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		{
			new_cmd = create_new_command(token, cmd_id, paths);
			new_cmd->cmd_id = cmd_id;
			// Aquí determinamos si este comando es el último
			if (current->next == NULL)  // Es el último nodo
				new_cmd->last_cmd = 1;
			else
				new_cmd->last_cmd = 0;
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
		cmd_id ++;
		current = current->next;
	}
	return (commands_list);
}

int	add_details_to_cmd_list(t_list *commands_list, t_list *token_list)
{
	t_list		*current;
	t_list		*cmd_node;
	t_cmd		*cmd;
	t_tokens	*token;

	current = token_list;
	while (current)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		{
			cmd_node = commands_list;
			while (cmd_node)
			{
				cmd = (t_cmd *)cmd_node->content;
				if (ft_strcmp(cmd->cmd, token->str) == 0)
				{
					count_args(current, cmd);
					add_args(&cmd, current);
					break ;
				}
				cmd_node = cmd_node->next;
			}
			if (!cmd_node)
			{
				fprintf(stderr, "Error: Comando '%s' no encontrado en la lista de comandos.\n", token->str);
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}