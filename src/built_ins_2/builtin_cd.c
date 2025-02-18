/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:04:01 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/18 20:00:45 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:24:47 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/18 13:53:52 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cd_handle_no_args(t_list *env_list, char **path_home)
{
	*path_home = get_variable_in_env_list(env_list, "HOME");
	if (!(*path_home))
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
	}
	else
	{
		*path_home = ft_strdup(*path_home);
	}
}

static void	cd_with_dash(t_list *env_list, char **path_home)
{
	*path_home = get_variable_in_env_list(env_list, "OLDPWD");
	if (!(*path_home))
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return ;
	}
	ft_putstr_fd(*path_home, 1);
	write(1, "\n", 1);
	*path_home = ft_strdup(*path_home);
}

void	check_pwd_exist(char **pwd)
{
	if (!(*pwd))
	{
		perror("cd");
	}
}


static int	handle_cd_errors(char *new_path, char *old_pwd)
{
	if (chdir(new_path) == -1)
	{
		perror("cd");
		free(old_pwd);
		free(new_path);
		return (1);
	}
	return (0);
}

/**
 * cd_change_directory - change the current directory and udpate `PWD` y `OLDPWD`.
 * @param new_path
 * @param mini
 */
static void	cd_change_directory(char *new_path, t_mini *mini)
{
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("cd");
		free(new_path);
		return ;
	}
	if (handle_cd_errors(new_path, old_pwd))
        return ;
	update_var_exist("OLDPWD", old_pwd, &(mini->env));
	free(old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("cd");
		return ;
	}
	update_var_exist("PWD", new_pwd, &(mini->env));
	free(new_pwd);
}
	// change directory
	// if (chdir(new_path) == -1)
	// {
	// 	perror("cd");
	// 	free(old_pwd);
	// 	free(new_path);
	// 	return ;
	// }

/**
 * handle cases:
 * 
 * 1. "cd" with no arguments: change to the user's home directory | chdir("..")
 * 2. "cd ../dir_anterior" navegar al directorio padre | chdir("../dir_anterior")
 * 3. "cd /path_x" with a path: change to absolute path | chdir("/path_x") 
 * 4. "cd ruta_x" relative path: | chdir("./ruta_x")
 * 5. "cd -" change to $OLDPWD | chdir("-")
 */

void	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*new_path;

	if (!mini || !mini->env)
		return ;

	new_path = NULL;

	if (!cmd->cmd_args[1])
	{
		cd_handle_no_args(mini->env, &new_path);
	}
	else if ((ft_strcmp(cmd->cmd_args[1], "-") == 0) && !cmd->cmd_args[2])
	{
		cd_with_dash(mini->env, &new_path);
	}
	else
	{
		// if is  `..`, `../dir_forward`, `/path_x` o `path_x`
		new_path = ft_strdup(cmd->cmd_args[1]);
	}
	cd_change_directory(new_path, mini);
}

	/*
	old_pwd = getcwd(NULL, 0);
	check_pwd_exist(&old_pwd);
	// change directory
	if (chdir(new_path) == -1)
	{
		perror("cd");
		free(old_pwd);
		return ;
	}
	update_var_exist("OLDPWD", old_pwd, &(mini->env));
	free(old_pwd);

	new_pwd = getcwd(NULL, 0);
	check_pwd_exist(&new_pwd);

	update_var_exist("PWD", new_pwd, &(mini->env));
	free(new_pwd);
}
*/
