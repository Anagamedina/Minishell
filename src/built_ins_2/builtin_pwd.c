/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:04:01 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 12:26:33 by dasalaza         ###   ########.fr       */
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

int	ft_pwd(t_mini *mini)
{
	char	*curr_dir;
	char	*env_var;

	curr_dir = NULL;
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
	{
		env_var = get_variable_in_env_list(mini->env, "PWD=");
		if (env_var)
		{
			ft_putstr_fd(env_var, 1);
			write(1, "\n", 1);
		}
		else
			ft_putstr_fd("Error: PWD not set\n", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd(curr_dir, 1);
		write(1, "\n", 1);
	}
	free(curr_dir);
	return (0);
}
