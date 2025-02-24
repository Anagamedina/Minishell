/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:55:27 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/24 21:26:15 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 10:11:15 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 12:40:41 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_variable_in_env_list(t_list **env_list, char *key, char *new_value)
{
	t_list	*current_node;
	t_env	*var;

	if (!env_list || !key)
		return (0);
	current_node = *env_list;
	while (current_node)
	{
		var = (t_env *) current_node->content;
		if (ft_strcmp(var->key, key) == 0)
		{
			free(var->value);
			if (new_value != NULL)
				var->value = ft_strdup(new_value);
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

int	update_existing_env_variable(t_list **env_list, char *name, char *value)
{
	if (set_variable_in_env_list(env_list, name, value) == TRUE)
	{
		free(name);
		if (value)
			free(value);
		return (TRUE);
	}
	return (FALSE);
}

void	error_export_syntax(char *var_name)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(var_name, 2);
	ft_putendl_fd("`: not a valid identifier", 2);
}

static int	add_new_env_variable(t_list **env, char *var_name, char *var_value)
{
	t_list	*new_var_env;

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

static void	add_or_update_env_variable(t_list **env_list, char *arg)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(arg);
	var_value = get_var_value(arg);
	if (!var_name)
	{
		error_export_syntax(arg);
		free(var_value);
		return ;
	}
	if (!update_existing_env_variable(env_list, var_name, var_value))
		add_new_env_variable(env_list, var_name, var_value);
}

/**
 *
 * export abc
 * export abc=123
 * export abc=123  def=456
 */

int	ft_export(t_cmd *curr_cmd, t_mini *mini)
{
	int	i;
	int	error_flag;

	error_flag = 0;
	i = 1;
	while (curr_cmd->cmd_args[i] != NULL)
	{
		if (!validate_syntax_name_value(curr_cmd->cmd_args[i]))
		{
			error_export_syntax(curr_cmd->cmd_args[i]);
			error_flag = 1;
		}
		else
			add_or_update_env_variable(&(mini->env), curr_cmd->cmd_args[i]);
		i ++;
	}
	if (mini->envp_to_array)
		free_string_matrix(mini->envp_to_array);
	mini->envp_to_array = env_list_to_array(mini->env);
	if (!mini->envp_to_array)
		return (1);
	return (error_flag);
}

/**
 * ft_strjoin_export - concat two strings with a character separator.
 *
 * - `c`: character separator (default: `=`).
 * A string in the format `s1=c+s2`.
 */

char	*ft_strjoin_export(const char *s1, const char *s2, char c)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!result)
		return (NULL);
	if (s1)
		ft_memcpy(result, s1, len1);
	result[len1] = c;
	if (s2)
		ft_memcpy(result, s2, len2);
	result[len1 + len2 + 1] = '\0';
	return (result);
}
