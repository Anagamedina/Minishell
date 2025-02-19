/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:51:03 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/19 15:55:03 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *file, int type)
{
	int	fd;

	if (type == REDIR_IN)
		fd = open(file, O_RDONLY);
	else if (type == REDIR_OUT) 
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APPEND) 
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
	return (fd);
}

int	handle_input_redirection(t_cmd *cmd, t_redir *curr_redir)
{
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	cmd->input_fd = open_file(curr_redir->filename, REDIR_IN);
	if (cmd->input_fd == -1)
	{
		perror("Error abriendo archivo de entrada");
		return (FALSE);
	}
	return (TRUE);
}

int	handle_output_redirection(t_cmd *cmd, t_redir *curr_redir)
{
	if (cmd->output_fd != STDIN_FILENO)
		close(cmd->output_fd);
	cmd->output_fd = open_file(curr_redir->filename, REDIR_OUT);
	if (cmd->output_fd == -1)
	{
		perror("Error abriendo archivo de SALIDA");
		return (FALSE);
	}
	return (TRUE);
}

int	apply_redirections(t_cmd *cmd)
{
	t_list	*redir_node;
	t_redir	*curr_redir;
	int		redirection_applied;

	redir_node = cmd->redir_list;
	redirection_applied = 0;
	while (redir_node)
	{
		curr_redir = (t_redir *)redir_node->content;
		if (curr_redir->type == HEREDOC)
		{
			if (handle_input_redirection(cmd, curr_redir) == TRUE)
				redirection_applied = 1;
		}
		if (curr_redir->type == REDIR_IN)
		{
			if (handle_input_redirection(cmd, curr_redir) == TRUE)
				redirection_applied = 1;
		}
		if (curr_redir->type == REDIR_OUT || curr_redir->type == REDIR_APPEND)
		{
			if (handle_output_redirection(cmd, curr_redir) == TRUE)
				redirection_applied = 1;
		}
		redir_node = redir_node->next;
	}
	return (redirection_applied);
}
