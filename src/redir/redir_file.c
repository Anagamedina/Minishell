/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:51:03 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 23:39:43 by anamedin         ###   ########.fr       */
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
		// fprintf(stderr, "Error al abrir '%s': ", file);
		// perror("");
		return (-1);
	}
	return (fd);
}

static	void	apply_input_redirection(t_cmd *cmd, t_redir *curr_redir, \
		int *redir_applied)
{
	if (curr_redir->type == HEREDOC)
	{
		if (handle_input_redirection(cmd, curr_redir) == TRUE)
			*redir_applied = 1;
	}
	if (curr_redir->type == REDIR_IN)
	{
		if (handle_input_redirection(cmd, curr_redir) == TRUE)
			*redir_applied = 1;
	}
}

static	void	apply_output_redirection(t_cmd *cmd, t_redir *curr_redir, \
		int *redir_applied)
{
	if (curr_redir->type == REDIR_OUT || curr_redir->type == REDIR_APPEND)
	{
		if (handle_output_redirection(cmd, curr_redir) == TRUE)
			*redir_applied = 1;
	}
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
		apply_input_redirection(cmd, curr_redir, &redirection_applied);
		apply_output_redirection(cmd, curr_redir, &redirection_applied);
		redir_node = redir_node->next;
	}
	return (redirection_applied);
}
