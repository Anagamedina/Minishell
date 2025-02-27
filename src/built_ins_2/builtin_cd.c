/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:45:15 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/27 18:20:59 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int cd_without_args(t_list *env_list, char **path_home)
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

static int cd_with_dash(t_list* env_list, char** path_home, int has_tilde)
{
	char	*old_pwd;

	old_pwd = get_variable_in_env_list(env_list, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (access(old_pwd, F_OK) == -1)
	{
		ft_putstr_fd("cd: no such file or directory\n", 2);
		return (1);
	}
	*path_home = ft_strdup(old_pwd);
	if (!(*path_home))
	{
		ft_putendl_fd("cd: error: memory allocation failed", 2);
		return (1);
	}
	if (has_tilde == 0)
	{
		ft_putstr_fd(*path_home, 1);
		write(1, "\n", 1);
	}
	return(0);
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

/**
 * cd_change_directory - change the current directory
 * and update `PWD` y `OLDPWD`.
 * if fail getcwd() try to use `$PWD`
 * if fail $PWD , we show an error and move to `/` (root) with chdir()
 * @param new_path
 * @param mini
 */
static int	cd_change_directory(char *new_path, t_mini *mini)
{
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		old_pwd = get_variable_in_env_list(mini->env, "PWD");
		if (old_pwd)
			old_pwd = ft_strdup(old_pwd);
		else
		{
			ft_putendl_fd("cd: error: cannot determine current directory", 2);
			return (1);
		}
	}
	if (handle_cd_errors(new_path) == 1)
	{
		if (old_pwd)
			free(old_pwd);
		return (1);
	}

	set_variable_in_env_list(&(mini->env), "OLDPWD", old_pwd);
	free(old_pwd);

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd("cd: error: lost directory, moving to /\n", 2);
		chdir("/");
		set_variable_in_env_list(&(mini->env), "PWD", "/");
		return (0);
	}

	set_variable_in_env_list(&(mini->env), "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

/**
 * handle cases:
 * 
 * 1. "cd" with no arguments: change to the user's home directory | chdir("..")
 * 2. "cd ../dir_anterior" navegar al directorio padre | chdir("../dir_anterior")
 * 3. "cd /path_x" with a path: change to absolute path | chdir("/path_x") 
 * 4. "cd ruta_x" relative path: | chdir("./ruta_x")
 * 5. "cd -" change to $OLDPWD | chdir("-")
 */

int	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*new_path;
	int		is_a_tilde;
	int		status;

	new_path = NULL;
	is_a_tilde = 0;
	status = 0;
	if (!cmd->cmd_args[1])
		status = cd_without_args(mini->env, &new_path);
	else if (ft_strcmp(cmd->cmd_args[1], "-") == 0 && !cmd->cmd_args[2])
		status = cd_with_dash(mini->env, &new_path, is_a_tilde);
	else if (ft_strcmp(cmd->cmd_args[1], "~") == 0 && !cmd->cmd_args[2])
		status = cd_with_dash(mini->env, &new_path, 2);
	else
	{
		new_path = ft_strdup(cmd->cmd_args[1]);
		if (!new_path)
		{
			ft_putendl_fd("cd: error: memory allocation failed", 2);
			return (1);
		}
	}
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
