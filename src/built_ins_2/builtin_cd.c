/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:45:15 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 01:49:32 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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


int	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*new_path;
	int		status;

	if (cmd->count_args > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		return (1);
	}
	new_path = get_cd_path(mini, cmd, &status);
	if (status == 1 || !new_path || new_path[0] == '\0')
	{
		ft_putstr_fd("Error: cd: invalid path\n", 2);
		free(new_path);
		return (1);
	}
	status = cd_change_directory(new_path, mini);
	free(new_path);
	return (status);
}
