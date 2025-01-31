/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/31 18:40:49 by anamedin         ###   ########.fr       */
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

		// Si encontramos un comando externo o un built-in
		if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
		{
			// Si ya se procesó un comando, detente (esto sucede después de un PIPE)
			if (cmd->count_args > 0)
				break;

			// Guardamos el comando y lo contamos como el primer argumento
			cmd->cmd = token->str;
			cmd->count_args = 1;
		}
			// Si encontramos un delimitador (PIPE), detenemos el procesamiento del comando actual
		else if (token->type_token == PIPE || token->type_token == DELIMITER || token->type_token == REDIR_IN || token->type_token == REDIR_OUT || token->type_token == REDIR_APPEND)
		{
			break;
		}
		else if (token->type_token == WORD)
		{
			// Si es un argumento válido, lo contamos
			cmd->count_args ++;
		}

		current = current->next;
	}
}

void add_args(t_cmd **cmd, t_list *token_list)
{
	t_list      *current;
	t_tokens    *token;
	int         j = 0;

	if (!cmd || (*cmd)->count_args <= 0)
		return;

	// Reserva memoria para cmd_args con un tamaño adecuado
	(*cmd)->cmd_args = ft_calloc((*cmd)->count_args + 1, sizeof(char *));
	if (!(*cmd)->cmd_args)
		return;

	current = token_list;
	// Primero, agrega el comando (que es el primer token)
	token = (t_tokens *)current->content;
	if (token->type_token == CMD_EXTERNAL || token->type_token == BUILTINS)
	{
		(*cmd)->cmd_args[j] = ft_strdup(token->str);
		if (!(*cmd)->cmd_args[j])
		{
			perror("Error al duplicar el comando");
			while (--j >= 0)
				free((*cmd)->cmd_args[j]);
			free((*cmd)->cmd_args);
			return;
		}
		j++;
	}

	// Ahora, agrega los argumentos (tokens de tipo WORD)
	current = current->next; // Avanza al siguiente token
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
				return;
			}
			j++;
		}
		current = current->next;
	}

	(*cmd)->cmd_args[j] = NULL; // Asegura que el último índice sea NULL
}