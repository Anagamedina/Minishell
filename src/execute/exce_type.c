/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:54:12 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/18 12:03:43 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin_command(char *cmd)
{
	return (ft_strcmp(cmd, ECHO) == 0 || ft_strcmp(cmd, EXPORT) == 0 || \
		ft_strcmp(cmd, UNSET) == 0 || ft_strcmp(cmd, ENV) == 0 || \
		ft_strcmp(cmd, CD) == 0 || ft_strcmp(cmd, PWD) == 0 || \
		ft_strcmp(cmd, EXIT) == 0);
}

int	is_cmd_external(t_mini *mini, t_tokens *token)
{
	char		**paths;
	char		**env_var_array;
	char		*cmd_path;

	if (!mini || !mini->tokens)
		return FALSE;
	env_var_array = env_list_to_array(mini->env);
	paths = get_path(env_var_array);
	if (env_var_array != NULL)
	{
		free_string_matrix(env_var_array);
	}
	cmd_path = get_cmd_path(token, paths);
	if (cmd_path != NULL)
	{
		free(cmd_path);
		return (TRUE);
	}
	return (FALSE);
}

