/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/18 11:57:39 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void count_args(t_list *token_list, t_cmd *cmd)
{
	t_list      *current;
	t_tokens    *token;

	if (!token_list || !cmd)
		return;

	current = token_list;
	cmd->count_args = 0;

	while (current)
	{
		token = (t_tokens *)current->content;

		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		{
			if (cmd->count_args > 0)
				break;
			cmd->cmd = token->str;
			cmd->count_args = 1;
		}
		else if (token->type_token == PIPE || token->type_token == DELIMITER || token->type_token == REDIR_IN || token->type_token == REDIR_OUT || token->type_token == REDIR_APPEND || token->type_token == HEREDOC)
			break;
		else if (token->type_token == WORD)
			cmd->count_args ++;
		current = current->next;
	}
}

int	init_cmd_args(t_cmd **cmd)
{
	if (!cmd || (*cmd)->count_args <= 0)
		return (0);
	(*cmd)->cmd_args = ft_calloc((*cmd)->count_args + 1, sizeof(char *));
	if (!(*cmd)->cmd_args)
		return (0);
	return (1);
}

void	assign_cmd_args(t_cmd **cmd, t_list *token_list)
{
	t_list		*current = token_list;
	t_tokens	*token;
	int			j = 0;

	while (current && j < (*cmd)->count_args)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS || token->type_token == WORD)
		{
			(*cmd)->cmd_args[j] = ft_strdup(token->str);
			if (!(*cmd)->cmd_args[j])
			{
				perror("Error al duplicar argumento");
				while (--j >= 0)
					free((*cmd)->cmd_args[j]);
				free((*cmd)->cmd_args);
				return;
			}
			j++;
		}
		current = current->next;
	}
	(*cmd)->cmd_args[j] = NULL;
}

void	add_args(t_cmd **cmd, t_list *token_list)
{
	if (!init_cmd_args(cmd))
		return;
	assign_cmd_args(cmd, token_list);
}