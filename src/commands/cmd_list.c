/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:39:34 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/10 12:32:15 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*get_last_command(t_list *commands_list)
{
	if (!commands_list)
		return (NULL);
	while (commands_list->next)
		commands_list = commands_list->next;
	return ((t_cmd *)commands_list->content);
}

void	process_token(t_list **commands_list, t_list *token_list, \
		char **paths, int *cmd_id)
{
	t_tokens	*token;

	token = (t_tokens *)token_list->content;
	if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		add_command_to_list(commands_list, token, paths, cmd_id);
	else if (*commands_list)
		add_redirection((t_cmd *)(ft_lstlast(*commands_list)->content),
			token_list);
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
		process_token(&commands_list, token_list, paths, &cmd_id);
		if (commands_list != NULL)
			token_list = token_list->next;
		else
			return (NULL);
	}
	if (commands_list)
	{
		last_cmd = get_last_command(commands_list);
		if (last_cmd)
			last_cmd->last_cmd = 1;
	}
	return (commands_list);
}

void	process_command_node(t_list *cmd_node, t_tokens *token, \
		t_list *current, int *cmd_count)
{
	t_cmd	*cmd;

	while (cmd_node)
	{
		cmd = (t_cmd *)cmd_node->content;
		if (cmd && cmd->cmd_id == *cmd_count)
		{
			process_command_args(current, cmd);
			(*cmd_count)++;
			break ;
		}
		cmd_node = cmd_node->next;
	}
	if (!cmd_node)
		printf("Error: Command '%s' not found.\n", token->str);
}

int	add_details_to_cmd_list(t_list *commands_list, t_list *token_list)
{
	t_list		*current;
	t_tokens	*token;
	int			cmd_count;

	if (!commands_list || !token_list)
		return (0);
	current = token_list;
	cmd_count = 1;
	while (current)
	{
		token = (t_tokens *)current->content;
		if (!token)
		{
			current = current->next;
			continue ;
		}
		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
			process_command_node(commands_list, token, current, &cmd_count);
		current = current->next;
	}
	return (0);
}
