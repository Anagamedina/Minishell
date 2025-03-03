/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:30:45 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/25 15:19:01 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*void	count_args(t_list *token_list, t_cmd *cmd)
{
	t_list		*current;
	t_tokens	*token;

	if (!token_list || !cmd)
		return ;
	current = token_list;
	cmd->count_args = 0;

	while (current)
	{
		token = (t_tokens *)current->content;

		// Si encontramos un nuevo comando después de `|`, reiniciar el contador
		if (token->type_token == PIPE)
			break;

		// Asignar nombre del comando (pero solo si es el primer token del comando)
		if ((token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS) && cmd->count_args == 0)
		{
			cmd->cmd = ft_strdup(token->str);
			cmd->count_args = 1;
		}
		else if (token->type_token == WORD)
		{
			cmd->count_args++;
		}
		current = current->next;
	}
}*/

void count_args(t_list *token_list, t_cmd *cmd)
{
	t_list *current;
	t_tokens *token;

	if (!token_list || !cmd)
		return;

	current = token_list;
	cmd->count_args = 0;

	while (current)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == PIPE)
			break;
		if ((token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS) && cmd->count_args == 0)
		{
			cmd->cmd = ft_strdup(token->str);
			cmd->count_args++;
		}
		else if (token->type_token == WORD)
		{
			cmd->count_args++;
		}
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
	t_list		*current;
	t_tokens	*token;
	int			j;

	j = 0;
	current = token_list;
	while (current && j < (*cmd)->count_args)
	{
		token = (t_tokens *)current->content;
		if (token->type_token == PIPE)
			break ;
		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS \
				|| token->type_token == WORD)
		{
			(*cmd)->cmd_args[j] = ft_strdup(token->str);
			if (!(*cmd)->cmd_args[j])
			{
				perror("Error al duplicar argumento");
				// free_cmd(&cmd);
				// free_cmd_args(*cmd);
				return ;
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
		return ;
	assign_cmd_args(cmd, token_list);
}
