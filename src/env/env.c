/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/14 22:03:30 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validate_syntax_name_value(char *new_local_var)
{
	if (!(validate_var_name(new_local_var)))
		return (FALSE);
	if (!(validate_var_value(new_local_var)))
		return (FALSE);
	return (TRUE);
}

static int	add_env_node(t_list **env_list, char *env_var)
{
	t_env	*new_env;
	t_list	*new_node;

	new_env = create_env_node(env_var);
	if (!new_env)
	{
		return (FALSE);
	}
	new_node = ft_lstnew(new_env);
	if (!new_node)
	{
		free_env_node(new_env);
		return (FALSE);
	}
	ft_lstadd_back(env_list, new_node);
	return (TRUE);
}

t_list	*init_env_list(char **envp)
{
	t_list	*env_list;
	int		i;

	env_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (!add_env_node(&env_list, envp[i]))
		{
			free_env_list(&env_list);
			return (NULL);
		}
		i ++;
	}
	return (env_list);
}

void	print_str(char *cmd_str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(cmd_str, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

int	ft_env(t_list *env_list, t_cmd *cmd)
{
	t_list	*current;
	t_env	*env_var;

	if (!env_list)
		return (1);
	if (cmd->cmd_args && cmd->cmd_args[1] != NULL)
	{
		print_str(cmd->cmd_args[1]);
		return (127);
	}
	current = env_list;
	while (current)
	{
		env_var = (t_env *) current->content;
		if (!env_var || !env_var->key || !env_var->value || \
				ft_strcmp(env_var->value, "") == 0)
		{
			current = current->next;
			continue ;
		}
		printf("%s=%s\n", env_var->key, env_var->value);
		current = current->next;
	}
	return (0);
}
