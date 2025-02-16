/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:13:24 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/16 13:46:26 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int open_file(char *file, int type)
{
	int fd;

	if (type == REDIR_IN) // <
		fd = open(file, O_RDONLY);
	else if (type == REDIR_OUT) // >
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APPEND) // >>
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == HEREDOC)
	{
		unlink(file);
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else
		return (-1);

	if (fd == -1)
	{
		fprintf(stderr, "Error al abrir '%s': ", file);
		perror("");
	}
	else
		printf("Archivo abierto: %s, fd: %d\n", file, fd); // 📌 Imprimir el fd

	return (fd);
}

int apply_redirections(t_cmd *cmd)
{
	t_list *redir_node = cmd->redir_list;
	t_redir *curr_redir;
	int redirection_applied = 0;

	while (redir_node)
	{
		curr_redir = (t_redir *)redir_node->content;

		if (curr_redir->type == HEREDOC)
		{
			if (cmd->input_fd != STDIN_FILENO)
				close(cmd->input_fd);

			cmd->input_fd = open_file(curr_redir->filename, REDIR_IN); // 📌 Abrir en modo lectura
			if (cmd->input_fd == -1)
			{
				perror("Error abriendo archivo heredoc");
				return FALSE;
			}
			redirection_applied = 1;
		}
		if (curr_redir->type == REDIR_IN)
		{
			if (cmd->input_fd != STDIN_FILENO)
				close(cmd->input_fd);
			cmd->input_fd = open_file(curr_redir->filename, curr_redir->type);
			if (cmd->input_fd == -1)
			{
				perror("Error abriendo archivo de entrada");
				return FALSE;
			}
			redirection_applied = 1;
		}

		if (curr_redir->type == REDIR_OUT || curr_redir->type == REDIR_APPEND)
		{
			if (cmd->output_fd != STDOUT_FILENO)
				close(cmd->output_fd);
			cmd->output_fd = open_file(curr_redir->filename, curr_redir->type);
			if (cmd->output_fd == -1)
			{
				perror("Error abriendo archivo de salida");
				return FALSE;
			}
			redirection_applied = 1;
		}

		redir_node = redir_node->next;
	}
	return redirection_applied;
}