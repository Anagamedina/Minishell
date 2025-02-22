/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:04:01 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 16:00:53 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_mini *mini)
{
	char	*curr_dir;
	char	*env_var;

	if (!mini || mini->env == NULL)
	{
		ft_putstr_fd("Error: env not init\n", 2);
		return (1);
	}
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
	{
		env_var = get_variable_in_env_list(mini->env, "PWD");
		if (env_var)
		{
			write(1, env_var, ft_strlen(env_var));
			write(1, "\n", 1);
		}
		else
			ft_putstr_fd("Error: PWD not set\n", 2);
		return (0);
	}
	ft_putstr_fd(curr_dir, 1);
	write(1, "\n", 1);
	free(curr_dir);
	return (0);
}

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
