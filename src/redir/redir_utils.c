/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:44:20 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/22 17:44:23 by anamedin         ###   ########.fr       */
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
