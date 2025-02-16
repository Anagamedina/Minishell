/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:57:34 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/16 13:25:09 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int create_heredoc(t_redir *redir, int nbr_heredoc)
{
	int   fd_tmp;
	char *tmp_name;
	char *num_str;
	char *line;

	// 📌 Generar nombre único del archivo heredoc
	num_str = ft_itoa(nbr_heredoc);
	tmp_name = ft_strjoin("/tmp/heredoc", num_str);
	free(num_str);

	// 📌 Crear archivo temporal con `open_file()`
	fd_tmp = open_file(tmp_name, HEREDOC);
	if (fd_tmp == -1)
	{
		free(tmp_name);
		return (-1);
	}

	// 📌 Leer entrada del usuario y escribir en el archivo temporal
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->delimiter) == 0) // 📌 Comparar con `delimiter`
			break;
		write(fd_tmp, line, ft_strlen(line));
		write(fd_tmp, "\n", 1);
		free(line);
	}
	free(line);
	close(fd_tmp);

	// 📌 Guardar el nombre del archivo temporal en `redir`
	free(redir->filename);
	redir->filename = ft_strdup(tmp_name);
	free(tmp_name);

	return (0);
}


//manejar multiples heredocs en una linia de comandos
//perite que multiples heredocs en un solo comando o en varios comandos
//se gestionen correctamente

int heredoc(t_cmd *cmd)
{
	t_list  *redir_node = cmd->redir_list;
	t_redir *curr_redir;
	int      nbr_heredoc = 0;

	while (redir_node)
	{
		curr_redir = (t_redir *)redir_node->content;

		if (curr_redir->type == HEREDOC)
		{
			if (create_heredoc(curr_redir, nbr_heredoc) == -1)
			{
				perror("Error creando heredoc");
				return (-1);
			}
			nbr_heredoc++;
		}
		redir_node = redir_node->next;
	}
	return (0);
}