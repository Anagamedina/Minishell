/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:07:06 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/04 11:10:59 by anamedin         ###   ########.fr       */
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

int	find_and_process_command(t_list *commands_list, t_tokens *token)
{
	t_list	*cmd_node;
	t_cmd	*cmd;

	cmd_node = commands_list;
	while (cmd_node)
	{
		cmd = (t_cmd *)cmd_node->content;
		if (cmd && cmd->cmd && token->str && !ft_strcmp(cmd->cmd, token->str))
		{
			process_command_args(cmd_node, cmd);
			return (0);
		}
		cmd_node = cmd_node->next;
	}
	printf("Error: Command '%s' not found.\n", token->str);
	return (-1);
}

int	add_details_to_cmd_list(t_list *commands_list, t_list *token_list)
{
	t_list		*current;
	t_tokens	*token;
	int			result;

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
			result = find_and_process_command(commands_list, token);
			if (result == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
