/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:49:24 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/18 10:30:35 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by daruuu on 11/18/24.
//

#include "../../includes/minishell.h"

// TODO: norminette
int	ft_pwd(t_mini *mini)
{
	char	*curr_dir;
	t_list	*mini_env;
	t_env	*env_var;

	if (!mini || mini->env == NULL)
	{
		write(2, "Error: env not init\n", 20);
		return (1);
	}
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
	{
		mini_env = mini->env;
		while (mini_env)
		{
			env_var = (t_env *) mini_env->content;
			if (ft_strcmp(env_var->key, "PWD") == 0)
			{
				write(1, env_var->value, ft_strlen(env_var->value));
				write(1, "\n", 1);
				return (0);
			}
			mini_env = mini_env->next;
		}
	}
	write(1, curr_dir, ft_strlen(curr_dir));
	write(1, "\n", 1);
	free(curr_dir);
	return (TRUE);
}
