/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:24:47 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/16 13:43:20 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

/**
 *
 * we need to handle the following cases:
 * 1. cd with no arguments: change to the user's home directory
 * 2. cd with a path: change to the specified directory
 * 3. cd with a relative path: change to the specified directory relative to the current working directory
 */
void	ft_cd(t_mini *mini, t_cmd *cmd)
{
	char	*path_home;
	char	*old_pwd;
	char	*new_pwd;

	if (!mini || !mini->env)
		return ;
	// IF ARGS NOT EQUAL TO 1
	if (!cmd->cmd_args[1])
	{
		path_home = (char *)find_env_var(mini->env, "HOME");
		if (!path_home)
		{
			// ft_putstr_fd("cd: HOME not set\n", 2);
			write(2, "cd: HOME not set\n", 17);
			return ;
		}
	}
	// IF ARG EQUAL TO 1 AND IS '-'
	// WE NEED TO USE 'OLDPWD'
	else if (cmd->cmd_args[1][0] == '-')
	{
		path_home = (char *)find_env_var(mini->env, "OLDPWD");
		if (!path_home)
		{
			// ft_putstr_fd("cd: OLDPWD not set\n", 2);
			write(2, "cd: OLDPWD not set\n", 20);
			return ;
		}
		ft_putstr_fd(path_home, 1);
		write(1, "\n", 1);
	}
	else
		path_home = cmd->cmd_args[1];
	// GET CURRENT WORKING DIRECTORY BEFORE CHANGE DIRECTORY
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("cd");
		return ;
	}

	printf("PATH_HOME: [%s]\n", path_home);

}