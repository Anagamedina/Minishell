/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 10:57:34 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/18 14:18:10 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char	*generate_heredoc_filename(int nbr_heredoc)
{
	char	*num_str;
	char	*tmp_name;

	num_str = ft_itoa(nbr_heredoc);
	if (!num_str)
		return (NULL);
	tmp_name = ft_strjoin("/tmp/heredoc", num_str);
	free(num_str);
	return (tmp_name);
}

int	write_heredoc_content(int fd_tmp, char *delimiter)
{
	char	*line;

	line = readline("> ");
	while (line && ft_strcmp(line, delimiter) != 0)
	{
		write(fd_tmp, line, ft_strlen(line));
		write(fd_tmp, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	return (0);
}

int	create_heredoc(t_redir *redir, int nbr_heredoc)
{
	int		fd_tmp;
	char	*tmp_name;

	tmp_name = generate_heredoc_filename(nbr_heredoc);
	if (!tmp_name)
		return (-1);
	fd_tmp = open_file(tmp_name, HEREDOC);
	if (fd_tmp == -1)
	{
		free(tmp_name);
		return (-1);
	}
	write_heredoc_content(fd_tmp, redir->filename);
	close(fd_tmp);
	free(redir->filename);
	redir->filename = ft_strdup(tmp_name);
	free(tmp_name);
	return (0);
}


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
