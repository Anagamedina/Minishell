/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:13:24 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/07 17:02:51 by dasalaza         ###   ########.fr       */
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
	if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	if (fd == -1)
		 perror("Error al abrir el archivo");
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
			cmd->input_fd = open_file(curr_redir->filename, REDIR_IN);
			redirection_applied = 1;
		}
		//CASO ACTUAL ES REDIR_OUT
		if (curr_redir->type == REDIR_OUT)
		{
			//Si ya hay una redirección de salida abierta y no es la salida estandar
			//PROTECCION 
			// if (cmd->output_fd != STDOUT_FILENO && cmd->output_fd != -1)
			if (cmd->output_fd != STDOUT_FILENO)
                close(cmd->output_fd); // Cerrar anterior si había otra redirección

            cmd->output_fd = open_file(curr_redir->filename, REDIR_OUT);
            if (cmd->output_fd == -1)
            {
                printf("Error: No se pudo abrir '%s'.\n", curr_redir->filename);
                return FALSE;
            }
            redirection_applied ++;
		}
		else if (curr_redir->type == REDIR_APPEND)
		{
			cmd->output_fd = open_file(curr_redir->filename, REDIR_APPEND);
			redirection_applied = 1;
		
		}
		if (cmd->input_fd == -1 && cmd->output_fd == -1)
		{
			printf("Error: No se pudo abrir el archivo '%s'.\n", curr_redir->filename);
			return (0);
		}

		redir_node = redir_node->next;
	}
	return redirection_applied;
}