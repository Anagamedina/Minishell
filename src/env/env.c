/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 16:30:40 by dasalaza         ###   ########.fr       */
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
		ft_lstclear(env_list, (void (*)(void *))free_env_node);
		return (FALSE);
	}
	new_node = ft_lstnew(new_env);
	if (!new_node)
	{
		free_env_node(new_env);
		ft_lstclear(env_list, (void (*)(void *))free_env_node);
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
			return (NULL);
		i ++;
	}
	return (env_list);
}

int	ft_env(t_list *env_list)
{
	t_list	*current;
	t_env	*env_var;

	if (!env_list)
		return (1);
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
