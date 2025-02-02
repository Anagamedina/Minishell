/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:13:24 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/02 13:59:04 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Abre un archivo según el tipo de redirección especificado
// type puede ser REDIR_IN (<), REDIR_OUT (>), o REDIR_APPEND (>>)
// Retorna el descriptor de archivo (fd) abierto o -1 si ocurre un error
int open_file(char *file, int type)
{
	int fd;

	// if (type == REDIR_IN)
	// 	fd = open(file, O_RDONLY);
	if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// else if (type == REDIR_APPEND)
	// 	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	 if (fd == -1)
		 perror("Error al abrir el archivo");
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

		// if (curr_redir->type == REDIR_IN)
		// {
		// 	cmd->input_fd = open_file(curr_redir->filename, REDIR_IN);
		// 	redirection_applied = 1;
		// }
		if (curr_redir->type == REDIR_OUT)
		{
			if (cmd->output_fd != STDOUT_FILENO && cmd->output_fd != -1)
                close(cmd->output_fd); // Cerrar anterior si había otra redirección

            cmd->output_fd = open_file(curr_redir->filename, REDIR_OUT);
            if (cmd->output_fd == -1)
            {
                printf("Error: No se pudo abrir '%s'.\n", curr_redir->filename);
                return FALSE;
            }
            redirection_applied = 1;
		}
		// else if (curr_redir->type == REDIR_APPEND)
		// {
		// 	cmd->output_fd = open_file(curr_redir->filename, REDIR_APPEND);
		// 	redirection_applied = 1;
		//
		// }
		// if (cmd->input_fd == -1 && cmd->output_fd == -1)
		// {
		// 	printf("Error: No se pudo abrir el archivo '%s'.\n", curr_redir->filename);
		// 	return (0);
		// }

		redir_node = redir_node->next;
	}
	return redirection_applied;
}















//CODIGO QUE NO SE USA///





// // Duplica un descriptor de archivo al descriptor de entrada o salida correspondiente
// // Luego cierra el descriptor original para evitar fugas de recursos

void	redirect_file(int fd, int target_fd)
{
	if (dup2(fd, target_fd) == -1)
	{
		perror("Error duplicando descriptor");
		exit(1);
	}
	if (close(fd) == -1)
	{
		perror("Error cerrando descriptor");
		exit(1);
	}
}

// // Maneja la redirección de entrada o salida de un comando
// // Abre el archivo correspondiente, redirige el descriptor de archivo y lo cierra
void	handle_redirection(char *file, t_cmd *cmd, int type)
{
	int fd;
	int target_fd;

	if (type == REDIR_IN) // <
		target_fd = cmd->input_fd;
	else if (type == REDIR_OUT) // >
		target_fd = cmd->output_fd;
	else
		return;

	fd = open_file(file, type);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	redirect_file(fd, target_fd);
	if (close(fd) == -1)
	{
		perror("Error closing file");
		exit(1);
	}
	free(file);
}
