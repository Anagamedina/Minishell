/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:13:24 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/31 17:06:23 by anamedin         ###   ########.fr       */
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
		 perror("Error al abrir el archivo");
	return (fd);
}






// // Duplica un descriptor de archivo al descriptor de entrada o salida correspondiente
// // Luego cierra el descriptor original para evitar fugas de recursos
void redirect_file(int fd, int target_fd)
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
void handle_redirection(char *file, t_cmd *cmd, int type)
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