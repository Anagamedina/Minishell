/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:36:31 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/07 16:25:43 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_env_value(char **new_value, char *existing, char *value)
{
	*new_value = ft_strjoin(existing, value);
	if (!*new_value)
		return (FALSE);
	return (TRUE);
}

int	set_variable_in_env_lst(t_list **env_lst, char *key, char *new_val)
{
	t_list	*current_node;
	t_env	*var;

	if (!env_lst || !key)
		return (0);
	current_node = *env_lst;
	while (current_node)
	{
		var = (t_env *) current_node->content;
		if (ft_strcmp(var->key, key) == 0)
		{
			free(var->value);
			if (new_val)
				var->value = ft_strdup(new_val);
			else
				var->value = ft_strdup("");
			return (1);
		}
		current_node = current_node->next;
	}
	return (0);
}

int	env_variable_exists(t_list *env_list, char *key_to_find)
{
	t_list	*current_node;
	t_env	*current_var;

	if (!key_to_find || !env_list)
		return (0);
	current_node = env_list;
	while (current_node)
	{
		current_var = (t_env *) current_node->content;
		if (ft_strcmp(current_var->key, key_to_find) == 0)
			return (TRUE);
		current_node = current_node->next;
	}
	return (FALSE);
}

int	add_new_env_variable(t_list **env, char *var_name, char *var_value)
{
	t_list	*new_var_env;

	new_var_env = NULL;
	new_var_env = create_new_env_node(var_name, var_value);
	if (!new_var_env)
	{
		ft_putendl_fd("Error: Failed to export variable\n", 2);
		free(var_name);
		if (var_value)
			free(var_value);
		return (FALSE);
	}
	ft_lstadd_back(env, new_var_env);
	return (TRUE);
}

int	update_env_var(t_list **env_lst, char *name, char *value, int flag)
{
	char	*new_value;
	char	*existing_value;
	int		result;

	if (!env_lst || !name)
		return (FALSE);
	existing_value = get_variable_in_env_list(*env_lst, name);
	new_value = value;
	if (flag == 1 && existing_value)
	{
		if (!append_env_value(&new_value, existing_value, value))
			return (FALSE);
	}
	result = set_variable_in_env_lst(env_lst, name, new_value);
	if (result == 1)
	{
		free(name);
		if (value && flag == 0)
			free(value);
		else if (flag == 1)
			free(new_value);
	}
	else if (flag == 1)
		free(new_value);
	return (result);
}
