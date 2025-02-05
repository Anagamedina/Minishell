/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:54:12 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/05 23:08:00 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin_command(char *cmd)
{
	return (strcmp(cmd, ECHO) == 0 || strcmp(cmd, EXPORT) == 0 || \
		strcmp(cmd, UNSET) == 0 || strcmp(cmd, ENV) == 0 || \
		strcmp(cmd, CD) == 0 || strcmp(cmd, PWD) == 0 || \
		strcmp(cmd, EXIT) == 0);
}

int	is_cmd_external(t_mini *mini, t_tokens *token)
{
	char		**paths;
	char		**env_var_array;
	char		*cmd_path;

	if (!mini || !mini->tokens)
		return FALSE;
	env_var_array = lst_to_arr(mini->env);
	paths = get_path(env_var_array);
	// if get_cmd path encuentra el token en las vars de entorno es por q existe
	if (env_var_array != NULL)
	{
		free_string_array(env_var_array);
	}
	cmd_path = get_cmd_path(token, paths);
	if (cmd_path != NULL)
	{
		free(cmd_path);
		return (TRUE);
	}
	return (FALSE);
}

