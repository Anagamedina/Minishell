/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:45:15 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 16:26:51 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd_without_args(t_list *env_list, char **path_home)
{
	char	*home;

	home = get_variable_in_env_list(env_list, "HOME");
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (1);
	}
	*path_home = ft_strdup(home);
	if (!(*path_home))
	{
		ft_putendl_fd("cd: error: memory allocation failed", 2);
		return (1);
	}
	return (0);
}

static int	cd_with_dash(t_list *env_list, char **path_home, int has_tilde)
{
	char	*tmp_path;

	if (has_tilde == 2)
	{
		tmp_path = get_variable_in_env_list(env_list, "HOME");
		if (!tmp_path)
			return (1);
	}
	else
	{
		tmp_path = get_variable_in_env_list(env_list, "OLDPWD");
		if (!tmp_path)
			return (1);
	}
	*path_home = ft_strdup(tmp_path);
	if (!(*path_home))
	{
		ft_putendl_fd("Error: memory allocation failed in cd_with_dash", 2);
		return (1);
	}
	if (has_tilde == 0)
		ft_putendl_fd(*path_home, 1);
	return (0);
}

static int	handle_cd_errors(char *new_path)
{
	if (!new_path)
	{
		ft_putendl_fd("cd: error: invalid path", 2);
		return (1);
	}
	if (chdir(new_path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

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

char	*get_cd_path(t_mini *mini, t_cmd *cmd, int *status)
{
	char	*new_path;

	new_path = NULL;
	*status = 0;
	if (!cmd->cmd_args[1])
		*status = cd_without_args(mini->env, &new_path);
	else if (ft_strcmp(cmd->cmd_args[1], "-") == 0 && !cmd->cmd_args[2])
		*status = cd_with_dash(mini->env, &new_path, 0);
	else if (ft_strcmp(cmd->cmd_args[1], "~") == 0 && !cmd->cmd_args[2])
		*status = cd_with_dash(mini->env, &new_path, 2);
	else
	{
		new_path = ft_strdup(cmd->cmd_args[1]);
		if (!new_path)
			ft_putendl_fd("cd: error: memory allocation failed", 2);
	}
	return (new_path);
}

int	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*new_path;
	int		status;

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
