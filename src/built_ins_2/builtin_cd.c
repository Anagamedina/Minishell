/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:45:15 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 17:23:50 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int cd_without_args(t_list *env_list, char **path_home)
{
	char	*home;

	home = get_variable_in_env_list(env_list, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	*path_home = ft_strdup(home);
	if (!(*path_home))
		return (1);
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
	*path_home = ft_strdup(old_pwd);
	if (has_tilde == 0)
	{
		ft_putstr_fd(*path_home, 1);
		write(1, "\n", 1);
	}
	return(0);
}

static int	handle_cd_errors(char *new_path)
{
	if (chdir(new_path) == -1)
	{
		perror("cd");
		free(new_path);
		return (1);
	}
	return (0);
}

/**
 * cd_change_directory - change the current directory
 * and update `PWD` y `OLDPWD`.
 * @param new_path
 * @param mini
 */
static int cd_change_directory(char* new_path, t_mini* mini)
{
	char	*new_pwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("cd");
		return (1);
	}
	if (handle_cd_errors(new_path) == 1)
		return (free(old_pwd), 1);
	update_var_exist("OLDPWD", old_pwd, &(mini->env));
	free(old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("cd");
		return (1);
	}
	update_var_exist("PWD", new_pwd, &(mini->env));
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
		new_path = ft_strdup(cmd->cmd_args[1]);
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
