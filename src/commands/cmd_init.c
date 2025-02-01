/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/01 21:23:37 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	new_cmd->is_builtin = -1;
	new_cmd->is_external = -1;
	new_cmd->last_cmd = -0;
	new_cmd->input_fd = -1;
	new_cmd->output_fd = -1;
	new_cmd->redir_list = NULL;
	new_cmd->next = NULL;

	return (new_cmd);
}

//TODO: remove cmd_id
t_cmd	*create_new_command(t_tokens *token, int cmd_id, char **paths)
{
	t_cmd *new_cmd = init_command();

	cmd_id ++;
	// printf("cmd_id: [%d]\n", cmd_id);
	if (!new_cmd)
		return NULL;

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
	else if (token->type_token == CMD_EXTERNAL)
	{
		new_cmd->is_external = 1; // Marcar como comando externo

		// Resolver la ruta del comando
		new_cmd->cmd_path = get_cmd_path(token, paths);
		if (!new_cmd->cmd_path)
		{
			fprintf(stderr, "Error: Comando externo '%s' no encontrado en las rutas proporcionadas.\n", token->str);
			free_command(new_cmd);
			return NULL;
		}
	}
	// add_redirection_to_cmd(new_cmd, token);
	return new_cmd;
}

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
			if (!new_cmd)
			{
				fprintf(stderr, "Error: Falló la creación del comando '%s'.\n", token->str);
				free_cmd_list(commands_list);
				return (NULL);
			}
			new_cmd->cmd_id = cmd_id++;
			// Aquí determinamos si este comando es el último
			if (current->next == NULL)  // Es el último nodo
				new_cmd->last_cmd = 1;
			else
				new_cmd->last_cmd = 0;
		}
		else if (is_redir(token) && new_cmd && current->next)
		{
			add_redirection_to_cmd(new_cmd, token, (t_tokens *)current->next->content);
			current = current->next;
			// continue;
		}
		if (new_cmd && (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS))
		{
			new_node = ft_lstnew(new_cmd);
			if (!new_node)
			{
				fprintf(stderr, "Error: No se pudo crear el nodo del comando.\n");
				free_command(new_cmd);
				free_cmd_list(commands_list);
				return NULL;
			}
			ft_lstadd_back(&commands_list, new_node);
		}
		/*
		else
		{
			current = current->next;
			continue;
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
		*/
		current = current->next;
	}
	return (commands_list);
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

		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		{
			cmd_node = commands_list;
			while (cmd_node)
			{
				cmd = (t_cmd *)cmd_node->content;

				if (strcmp(cmd->cmd, token->str) == 0)
				{
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