/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 12:55:26 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/04 12:54:54 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"


t_redir *init_redirection(t_tokens *token, t_tokens* next_token)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);

	if (next_token && next_token->type_token == FILENAME)
		new_redir->filename = ft_strdup(next_token->str);
	else
		new_redir->filename = NULL;

	if (!new_redir->filename)
	{
		perror("Error: al duplicar el nombre del archivo");
		free(new_redir);
		return (NULL);
	}
	new_redir->type = token->type_token;
	new_redir->fd_input = -1;
	new_redir->fd_output = -1;
	new_redir->next = NULL;
	return (new_redir);
}

void	add_redirection_to_cmd(t_cmd *cmd, t_tokens *redir_token, t_tokens* file_token)
{
	t_redir	*new_redir;
	t_list	*new_node;

	if (!cmd || !redir_token || !file_token)
        return;

    new_redir = init_redirection(redir_token, file_token);
    if (!new_redir)
        return;

    new_node = ft_lstnew(new_redir);
    if (!new_node)
    {
        free(new_redir->filename);
        free(new_redir);
        return;
    }

    if (!cmd->redir_list)
        cmd->redir_list = new_node;
    else
        ft_lstadd_back(&cmd->redir_list, new_node);
}


/*
void	add_redirection_to_cmd(t_cmd *cmd, t_tokens *token)
{
	t_redir	*new_redir;
	t_list	*new_node;

	new_redir = init_redirection(token);

	if (!new_redir)
		return ;

	new_node = ft_lstnew(new_redir);
	if (!new_node)
	{
		//free(new_redir->filename);
		//free(new_redir);
		return;
	}
	if (cmd->redir_list == NULL)
	{
		cmd->redir_list = new_node;
	}
	else
		ft_lstadd_back(&cmd->redir_list, new_node);

}
*/


// // Maneja la redirección de entrada con un valor predeterminado
// // Si el archivo de entrada no existe, crea un pipe vacío para continuar la ejecución
// // Devuelve 0 si la redirección es exitosa y 1 si se usa un flujo vacío
/*int input_redirect_with_default(char *file, t_cmd *cmd)
{
	int fd;
	int p_empty_fd[2];

	// Intentar abrir el archivo en modo lectura
	fd = open(file, O_RDONLY);
	if (fd == -1) {
		if (pipe(p_empty_fd) == -1) {
			perror("Error creating pipe");
			exit(1);
		}

		// Redirigir la entrada al pipe vacío
		if (dup2(p_empty_fd[0], cmd->input_fd) == -1) {
			perror("Error duplicating pipe");
			exit(1);
		}

		close(p_empty_fd[0]);
		close(p_empty_fd[1]);

		free(file);
		return 1;    // Continuar la ejecución con un flujo vacío
	}

	// Si el archivo existe, redirigir normalmente
	if (dup2(fd, cmd->input_fd) == -1)
	{
		perror("Error dup");
		exit(1);
	}
	close(fd);
	free(file);
	return 0;
}*/


