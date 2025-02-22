/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 21:45:15 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 15:53:58 by anamedin         ###   ########.fr       */
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

static void	cd_with_dash(t_list *env_list, char **path_home, int has_tilde)
{
	*path_home = get_variable_in_env_list(env_list, "OLDPWD");
	if (!(*path_home))
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return ;
	}
	if (has_tilde == 0)
	{
		ft_putstr_fd(*path_home, 1);
		write(1, "\n", 1);
	}
	*path_home = ft_strdup(*path_home);
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
	if (handle_cd_errors(new_path, old_pwd) == 1)
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

void	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*new_path;
	int		is_a_tilde;

	if (!mini || !mini->env)
		return ;
	new_path = NULL;
	is_a_tilde = 0;
	if (!cmd->cmd_args[1])
		cd_handle_no_args(mini->env, &new_path);
	else if (ft_strcmp(cmd->cmd_args[1], "-") == 0 && !cmd->cmd_args[2])
		cd_with_dash(mini->env, &new_path, is_a_tilde);
	else if (ft_strcmp(cmd->cmd_args[1], "~") == 0 && !cmd->cmd_args[2])
	{
		is_a_tilde = 2;
		cd_with_dash(mini->env, &new_path, is_a_tilde);
	}
	else
		new_path = ft_strdup(cmd->cmd_args[1]);
	if (!new_path)
	{
		ft_putstr_fd("Error: invalid path\n", 2);
		return ;
	}
	cd_change_directory(new_path, mini);
}
