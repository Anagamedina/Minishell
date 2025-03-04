/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:51:22 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/04 11:52:52 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_old_pwd(t_mini *mini)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		old_pwd = get_variable_in_env_list(mini->env, "PWD");
		if (old_pwd)
			return (ft_strdup(old_pwd));
		ft_putendl_fd("cd: error: cannot determine current directory", 2);
	}
	return (old_pwd);
}

int	cd_change_directory(char *new_path, t_mini *mini)
{
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = get_old_pwd(mini);
	if (!old_pwd)
		return (1);
	if (handle_cd_errors(new_path) == 1)
		return (free(old_pwd), 1);
	set_variable_in_env_list(&(mini->env), "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd("cd: error: lost directory, moving to /\n", 2);
		chdir("/");
		set_variable_in_env_list(&(mini->env), "PWD", "/");
		return (free(old_pwd), 0);
	}
	set_variable_in_env_list(&(mini->env), "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
