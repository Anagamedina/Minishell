/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:13:24 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/30 17:38:47 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Abre un archivo según el tipo de redirección especificado
// type puede ser REDIR_IN (<), REDIR_OUT (>), o REDIR_APPEND (>>)
// Retorna el descriptor de archivo (fd) abierto o -1 si ocurre un error
// int open_file(char *file, int type)
// {
// 	int fd;

// 	if (type == REDIR_IN)
// 		fd = open(file, O_RDONLY);
// 	else if (type == REDIR_OUT)
// 		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else if (type == REDIR_APPEND)
// 		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		return (-1);
// 	 if (fd == -1)
// 		 perror("Error al abrir el archivo");
// 	return (fd);
// }



// t_redir *init_redirection(t_cmd *cmd, t_tokens *token)
// {
// 	t_redir *new_redir = malloc(sizeof(t_redir));
// 	if (!new_redir)
// 		return (NULL);
// 	//copiar el nonbre del archivo asociado a la redirección
// 	new_redir->filename = ft_strdup(token->str);
// 	if (!new_redir->filename)
// 	{
// 		perror("Error: al duplicar el nombre del archivo");
// 		free(new_redir);
// 		return (NULL);
// 	}
// 	new_redir->type = token->type_token;
// 	new_redir->fd_input = -1;
// 	new_redir->fd_output = -1;
// 	new_redir->next = NULL;
// 	return (new_redir);
// }

// // Agrega una redirección a la lista de redirecciones del comando
// void add_redirection_to_cmd(t_cmd *cmd, t_tokens *token)
// {
// 	t_redir *new_redir = init_redirection(cmd, token);
// 	if (!new_redir)
// 		return;
// 	t_list *new_node = ft_lstnew(new_redir);
// 	if (!new_node)
// 	{
// 		//free(new_redir->filename);
// 		//free(new_redir);
// 		return;
// 	}
// 	if (!cmd->redir_list)
// 		cmd->redir_list = new_node;
// 	else
// 		ft_lstadd_back(&cmd->redir_list, new_node);

// }



// // Duplica un descriptor de archivo al descriptor de entrada o salida correspondiente
// // Luego cierra el descriptor original para evitar fugas de recursos
// void redirect_file(int fd, int target_fd)
// {
// 	if (dup2(fd, target_fd) == -1)
// 	{
// 		perror("Error duplicando descriptor");
// 		exit(1);
// 	}
// 	if (close(fd) == -1)
// 	{
// 		perror("Error cerrando descriptor");
// 		exit(1);
// 	}
// }

// // Maneja la redirección de entrada con un valor predeterminado
// // Si el archivo de entrada no existe, crea un pipe vacío para continuar la ejecución
// // Devuelve 0 si la redirección es exitosa y 1 si se usa un flujo vacío
// int input_redirect_with_default(char *file, t_cmd *cmd)
// {
// 	int fd;
// 	int p_empty_fd[2];

// 	// Intentar abrir el archivo en modo lectura
// 	fd = open(file, O_RDONLY);
// 	if (fd == -1) {
// 		if (pipe(p_empty_fd) == -1) {
// 			perror("Error creating pipe");
// 			exit(1);
// 		}

// 		// Redirigir la entrada al pipe vacío
// 		if (dup2(p_empty_fd[0], cmd->input_fd) == -1) {
// 			perror("Error duplicating pipe");
// 			exit(1);
// 		}

// 		close(p_empty_fd[0]);
// 		close(p_empty_fd[1]);

// 		free(file);
// 		return 1;    // Continuar la ejecución con un flujo vacío
// 	}

// 	// Si el archivo existe, redirigir normalmente
// 	if (dup2(fd, cmd->input_fd) == -1)
// 	{
// 		perror("Error dup");
// 		exit(1);
// 	}
// 	close(fd);
// 	free(file);
// 	return 0;
// }

// // Maneja la redirección de entrada o salida de un comando
// // Abre el archivo correspondiente, redirige el descriptor de archivo y lo cierra
// void handle_redirection(char *file, t_cmd *cmd, int type)
// {
// 	int fd;
// 	int target_fd;

// 	if (type == REDIR_IN) // <
// 		target_fd = cmd->input_fd;
// 	else if (type == REDIR_OUT) // >
// 		target_fd = cmd->output_fd;
// 	else
// 		return;

// 	fd = open_file(file, type);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		exit(1);
// 	}
// 	redirect_file(fd, target_fd);
// 	if (close(fd) == -1)
// 	{
// 		perror("Error closing file");
// 		exit(1);
// 	}
// 	free(file);
// }