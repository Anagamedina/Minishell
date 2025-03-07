/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:32:22 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 16:32:25 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin_command(char *cmd)
{
	return (ft_strcmp(cmd, ECHO_VAR) == 0 || ft_strcmp(cmd, EXPORT) == 0 || \
		ft_strcmp(cmd, UNSET) == 0 || ft_strcmp(cmd, ENV) == 0 || \
		ft_strcmp(cmd, CD) == 0 || ft_strcmp(cmd, PWD) == 0 || \
		ft_strcmp(cmd, EXIT) == 0);
}

char	*is_cmd_external(t_mini *mini, t_tokens *token)
{
	char	**paths;
	char	*cmd_path;

	if (!mini || !mini->tokens)
		return (NULL);
	paths = get_path(mini->envp_to_array);
	if (!paths)
		return (NULL);
	cmd_path = get_cmd_path(token, paths);
	free_string_matrix(paths);
	return (cmd_path);
}
