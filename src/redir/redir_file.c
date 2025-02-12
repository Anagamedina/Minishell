/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:13:24 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/12 14:55:48 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// Abre un archivo según el tipo de redirección especificado
// type puede ser REDIR_IN (<), REDIR_OUT (>), o REDIR_APPEND (>>)
// Retorna el descriptor de archivo (fd) abierto o -1 si ocurre un error

int open_file(char *file, int type)
{
	int fd;

	if (type == REDIR_IN)
		fd = open(file, O_RDONLY);
	else if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
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


/**
 * @brief Aplica las redirecciones especificadas en la lista de redirecciones de un comando.
 * 
 * Itera sobre la lista de redirecciones de un comando y aplica cada redirección.
 * Si se encuentra una redirección de entrada, se abre el archivo especificado y se
 * asigna el descriptor de archivo a input_fd.
 * Si se encuentra una redirección de salida, se abre el archivo especificado y se
 * asigna el descriptor de archivo a output_fd. Si ya existía una redirección de
 * salida anterior, se cierra el descriptor de archivo anterior.
 * Si se encuentra una redirección de appending, se abre el archivo especificado en
 * modo de appending y se asigna el descriptor de archivo a output_fd.
 * 
 * @param cmd El comando al que se le aplicarán las redirecciones.
 * 
 * @return 1 si se aplicaron redirecciones, 0 en caso contrario.
 */
int apply_redirections(t_cmd *cmd)
{
	t_list *redir_node = cmd->redir_list;
	t_redir *curr_redir;
	int redirection_applied = 0;

	while (redir_node)
	{
		curr_redir = (t_redir *)redir_node->content;

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