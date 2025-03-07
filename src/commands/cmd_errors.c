/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:29:09 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 23:56:21 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_empty_token(t_tokens *token, t_list *cmd_list)
{
	if (!token)
	{
		free_cmd_list(&cmd_list);
		return (FALSE);
	}
	return (TRUE);
}

int	error_cmd_creation(t_cmd *cmd, t_list *cmd_list)
{
	if (!cmd)
	{
		free_cmd_list(&cmd_list);
		return (FALSE);
	}
	return (TRUE);
}

int	error_node_creation(t_list *node, t_cmd *cmd, t_list *cmd_list)
{
	if (!node)
	{
		free_command(cmd);
		free_cmd_list(&cmd_list);
		return (FALSE);
	}
	return (TRUE);
}
