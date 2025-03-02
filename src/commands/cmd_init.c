/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:39:52 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/02 23:20:45 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	new_cmd->last_cmd = -1;
	new_cmd->input_fd = -1;
	new_cmd->output_fd = -1;
	new_cmd->has_pipe = -1;
	new_cmd->redir_list = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

/*t_cmd	*create_new_command(t_tokens *current_token, char **paths)
{
	t_cmd	*new_cmd;

	if (!current_token || !current_token->str)
		return (NULL);
	new_cmd = init_command();
	if (!new_cmd)
	{
		fprintf(stderr, "Error: No se pudo inicializar el comando\n");
		return (NULL);
	}
	new_cmd->cmd = ft_strdup(current_token->str);
	if (!new_cmd->cmd)
	{
		free_command(new_cmd);
		return (NULL);
	}
	if (current_token->type_token == BUILTINS)
		new_cmd->is_builtin = 1;
	else if (current_token->type_token == CMD_EXTERNAL)
	{
		new_cmd->is_external = 1;
		new_cmd->cmd_path = get_cmd_path(current_token, paths);
		if (!new_cmd->cmd_path)
		{
			printf("Error: '%s', paths not found\n", current_token->str);
			free_command(new_cmd);
			return (NULL);
		}
	}
	return (new_cmd);
}
*/

t_cmd	*create_new_command(t_tokens *current_token, char **paths)
{
	t_cmd	*new_cmd;

	if (!current_token || !current_token->str)
		return (NULL);
	new_cmd = init_command();
	if (!new_cmd)
	{
		write(2, "Error: No se pudo inicializar el comando\n", 41);
		return (NULL);
	}
	new_cmd->cmd = ft_strdup(current_token->str);
	if (!new_cmd->cmd)
	{
		free_command(new_cmd);
		return (NULL);
	}
	if (current_token->type_token == BUILTINS)
		new_cmd->is_builtin = 1;
	else if (current_token->type_token == CMD_EXTERNAL)
	{
		new_cmd->is_external = 1;
		new_cmd->cmd_path = get_cmd_path(current_token, paths);
		if (!new_cmd->cmd_path)
		{
			write(2, "bash: ", 6);
			write(2, current_token->str, ft_strlen(current_token->str));
			write(2, ": command not found\n", 20);
			new_cmd->cmd_path = NULL; // Permite que el pipe continúe
		}
	}
	return (new_cmd);
}

t_cmd	*get_last_command(t_list *commands_list)
{
	if (!commands_list)
		return (NULL);
	while (commands_list->next)
		commands_list = commands_list->next;
	return ((t_cmd *)commands_list->content);
}

t_list	*create_cmd_list(t_list *token_list, char **paths)
{
	t_list	*commands_list;
	int		cmd_id;
	t_cmd	*last_cmd;

	commands_list = NULL;
	cmd_id = 1;
	while (token_list)
	{
		if (((t_tokens *)token_list->content)->type_token == CMD_EXTERNAL
			|| ((t_tokens *)token_list->content)->type_token == BUILTINS)
			add_command_to_list(&commands_list, \
					(t_tokens *)token_list->content, paths, &cmd_id);
		else if (commands_list)
			add_redirection ((t_cmd *)(ft_lstlast(commands_list)->content), \
					token_list);
		token_list = token_list->next;
	}
	if (commands_list)
	{
		last_cmd = get_last_command(commands_list);
		if (last_cmd)
			last_cmd->last_cmd = 1;
	}
	return (commands_list);
}

int	add_details_to_cmd_list(t_list *commands_list, t_list *token_list)
{
	t_list		*current;
	t_list		*cmd_node;
	t_cmd		*cmd;
	t_tokens	*token;

	if (!commands_list || !token_list)
		return (0);
	current = token_list;
	while (current)
	{
		token = (t_tokens *)current->content;
		if (!token)
		{
			current = current->next;
			continue ;
		}
		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		{
			cmd_node = commands_list;
			//while (cmd_node && ((cmd = (t_cmd *)cmd_node->content)))
			while (cmd_node)
			{
				cmd = (t_cmd *) cmd_node->content;
				if (cmd && cmd->cmd && token->str && !ft_strcmp(cmd->cmd, token->str))
				{
					process_command_args(current, cmd);
					break ;
				}
				cmd_node = cmd_node->next;
			}
			if (!cmd_node)
				return (printf("Error: Command '%s' not found.\n", token->str), -1);
		}
		current = current->next;
	}
	return (0);
}
