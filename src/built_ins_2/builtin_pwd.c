/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:58:35 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/25 00:44:56 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
t_env *iterate_env(t_list *mini_env, t_env *env_var)
{
	while (mini_env)
	{
		env_var = (t_env *) mini_env->content;
		if (ft_strcmp(env_var->key, "PWD") == 0)
		{
			write(1, env_var->value, ft_strlen(env_var->value));
			write(1, "\n", 1);
			return ;
		}
		mini_env = mini_env->next;
	}
}
*/

void	update_pwd(t_mini *mini)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return ;
	set_variable_in_env_list((&mini->env), "OLDPWD", new_pwd);
	free(new_pwd);
}

int	ft_pwd(t_mini *mini)
{
	char	*curr_dir;
	char	*env_pwd;

	curr_dir = NULL;
	env_pwd = NULL;
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
	{
		env_pwd = get_variable_in_env_list(mini->env, "PWD=");
		if (env_pwd)
		{
			ft_putendl_fd(env_pwd, 1);
			return (1);
		}
		ft_putendl_fd("Error: PWD not set", 2);
		return (1);
	}
	ft_putendl_fd(curr_dir, 1);
	set_variable_in_env_list((&mini->env), "PWD", curr_dir);
	free(curr_dir);
	return (0);
}
