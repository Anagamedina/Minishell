/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:24:47 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/18 16:18:17 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	cd_without_arguments(t_list *env_list, char **path_home)
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
	// return ;
}

static void	cd_change_directory(char *new_path, t_mini *mini)
{
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	check_pwd_exist(&old_pwd);

	// change directory
	if (chdir(new_path) == -1)
	{
		perror("cd");
		free(old_pwd);
		free(new_path);
		return ;
	}

	update_var_exist("OLDPWD", old_pwd, &(mini->env));
	free(old_pwd);

	new_pwd = getcwd(NULL, 0);
	check_pwd_exist(&new_pwd);

	update_var_exist("PWD", new_pwd, &(mini->env));
	free(new_pwd);
	free(new_path);
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

void	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*new_path;
	// char	*old_pwd;
	// char	*new_pwd;

	if (!mini || !mini->env)
		return ;
	new_path = NULL;

	printf("cmd->cmd_arg[0] = %s\n", cmd->cmd_args[0]);
	printf("cmd->cmd_arg[1] = %s\n", cmd->cmd_args[1]);

	int condition1 = (ft_strcmp(cmd->cmd_args[1], "-"));

	printf("condition1 = %d\n", condition1);

	if (!cmd->cmd_args[1])
	{
		cd_without_arguments(mini->env, &new_path);
	}
	// else if ((ft_strcmp(cmd->cmd_args[1], "-") == TRUE) && !cmd->cmd_args[2])
	if (condition1 == 0)// && !cmd->cmd_args[2])
	{
		cd_with_dash(mini->env, &new_path);
	}
	else
	{
    	// if is  `..`, `../dir_anterior`, `/ruta_x` o `ruta_x`
		new_path = cmd->cmd_args[1];
	}
	cd_change_directory(new_path, mini);
}

	// old_pwd = getcwd(NULL, 0);
	// check_pwd_exist(&old_pwd);
	// // change directory
	// if (chdir(new_path) == -1)
	// {
	// 	perror("cd");
	// 	free(old_pwd);
	// 	return ;
	// }
	// update_var_exist("OLDPWD", old_pwd, &(mini->env));
	// free(old_pwd);

	// new_pwd = getcwd(NULL, 0);
	// check_pwd_exist(&new_pwd);

	// update_var_exist("PWD", new_pwd, &(mini->env));
	// free(new_pwd);

