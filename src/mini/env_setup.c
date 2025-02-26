/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:52:10 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/26 19:52:55 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_env_exist_in_env_list(t_list **env_list, char *var_name, char *default_value)
{
	t_list	*new_node;
	char	*env_value;

	if (!env_variable_exists(*env_list, var_name))
	{
		env_value = getenv(var_name);
		if (!env_value)
			env_value = default_value;
		new_node = create_new_env_node(var_name, ft_strdup(env_value));
		if (new_node)
			ft_lstadd_back(env_list, new_node);
	}
}

static void	check_pwd_exist_in_env_list(t_list **env_list)
{
	t_list	*new_node;
	char	*current_dir;

	if (!env_variable_exists(*env_list, PWD_ENV))
	{
		current_dir = getcwd(NULL, 0);
		if (!current_dir)
			current_dir = ft_strdup("/");
		new_node = create_new_env_node(PWD_ENV, current_dir);
		if (new_node)
			ft_lstadd_back(env_list, new_node);
	}
}

static void reset_shlvl(t_list **env_list)
{
	// t_list	*new_node;

	// if (!set_variable_in_env_list(env_list, SHLVL, "0"))
	set_variable_in_env_list(env_list, SHLVL, "0");
	// {
	// 	new_node = create_new_env_node(SHLVL, "0");
	// 	if (new_node)
	// 		ft_lstadd_back(env_list, new_node);
	// }
}

static void	increment_shlvl(t_list **env_list, char *shell_level)
{
	int		shlvl;
	char	*new_shlvl;

	shlvl = ft_atoi(shell_level);
	if (shlvl >= 100)
	{
		ft_putendl_fd(SHELL_LVL_WARNING, 2);
		new_shlvl = ft_strdup("1");
	}
	else
		new_shlvl = ft_itoa(shlvl + 1);

	if (new_shlvl)
	{
		if (!set_variable_in_env_list(env_list, "SHLVL", new_shlvl))
			perror("Error: Failed to update SHLVL");
		free(new_shlvl);
	}
}

void	configure_shell_env(t_list** env_list, char *shell_level)
{
	if (!env_list || !*env_list)
		return ;
	check_pwd_exist_in_env_list(env_list);
	check_env_exist_in_env_list(env_list, PATH_ENV, PATH_DEFAULT);
	check_env_exist_in_env_list(env_list, HOME_ENV, HOME_DEFAULT);
	check_env_exist_in_env_list(env_list, USER_ENV, "unknown");
	if (!shell_level || shell_level[0] == '-')
		reset_shlvl(env_list);
	else
		increment_shlvl(env_list, shell_level);
}