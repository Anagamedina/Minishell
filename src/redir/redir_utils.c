/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:44:20 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/10 01:23:18 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_input_redirection(t_cmd *cmd, t_redir *curr_redir)
{
	if (cmd->input_fd != STDIN_FILENO)
		close(cmd->input_fd);
	cmd->input_fd = open_file(curr_redir->filename, REDIR_IN);
	if (cmd->input_fd == -1)
	{
		write(2, "bash: ", 6);
		write(2, curr_redir->filename, ft_strlen(curr_redir->filename));
		write(2, ": No such file or directory\n", 28);
		return (FALSE);
	}
	return (TRUE);
}

int	handle_output_redirection(t_cmd *cmd, t_redir *curr_redir)
{
	if (cmd->output_fd >= 0 && cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	cmd->output_fd = open_file(curr_redir->filename, REDIR_OUT);
	if (cmd->output_fd == -1)
	{
		return (FALSE);
	}
	return (TRUE);
}

int	handle_append_redirection(t_cmd *cmd, t_redir *curr_redir)
{
	if (cmd->output_fd >= 0 && cmd->output_fd != STDOUT_FILENO)
		close(cmd->output_fd);
	cmd->output_fd = open_file(curr_redir->filename, REDIR_APPEND);
	if (cmd->output_fd == -1)
	{
		return (FALSE);
	}
	return (TRUE);
}

char	*generate_heredoc_filename(int nbr_heredoc)
{
	char	*num_str;
	char	*tmp_name;

	num_str = ft_itoa(nbr_heredoc);
	if (!num_str)
		return (NULL);
	tmp_name = ft_strjoin("/tmp/heredoc", num_str);
	free(num_str);
	if (!tmp_name)
		return (NULL);
	return (tmp_name);
}
