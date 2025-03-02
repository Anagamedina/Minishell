/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:55:30 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/02 22:37:54 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_variable(t_list **env_list, char *var_name)
{
	t_list	*current;
	t_list	*prev;
	t_env	*env_var;

	if (!env_list || !*env_list || !var_name)
		return ;
	current = *env_list;
	prev = NULL;
	while (current)
	{
		env_var = (t_env *) current->content;
		if (ft_strcmp(env_var->key, var_name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free_env(env_var);
			// free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(t_list **env_list, t_cmd *cmd)
{
	int	i;
	int	unset_path;

	unset_path = 0;
	i = 1;
	while (cmd->cmd_args[i])
	{
		if (ft_strcmp(cmd->cmd_args[i], PATH_ENV) == 0)
			unset_path = 1;
		unset_variable(env_list, cmd->cmd_args[i]);
		i ++;
	}
	if (unset_path)
		ft_putendl_fd("Warning: PATH variable unset, external may not work", 2);
	return (0);
}
