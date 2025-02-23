/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:55:27 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/23 18:18:28 by dasalaza         ###   ########.fr       */
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

int	update_var_exist(char *var_name, char *new_value, t_list **env_list)
{
	t_list	*current_node;
	t_env	*current_var;

	current_node = *env_list;
	while (current_node)
	{
		current_var = (t_env *)current_node->content;
		if (ft_strcmp(current_var->key, var_name) == 0)
		{
			free(current_var->value);
			if (new_value != NULL)
				current_var->value = ft_strdup(new_value);
			else
				current_var->value = ft_strdup("");
			return (TRUE);
		}
		current_node = current_node->next;
	}
	return (0);
}

int	check_if_var_name_exist(char *var_name, t_list *env_list)
{
	t_list	*current_node;
	t_env	*current_var;

	if (!var_name || !env_list)
		return (0);
	current_node = env_list;
	while (current_node)
	{
		current_var = (t_env *) current_node->content;
		if (ft_strcmp(var_name, current_var->key) == 0)
			return (TRUE);
		current_node = current_node->next;
	}
	return (FALSE);
}

static int	handle_existing_var(char *var_name, char *var_value, t_list **env)
{
	if (update_var_exist(var_name, var_value, env) == TRUE)
	{
		free(var_name);
		if (var_value)
			free(var_value);
		return (TRUE);
	}
	return (FALSE);
}

// static void	error_export_syntax(char *var_name)
void	error_export_syntax(char *var_name)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(var_name, 2);
	ft_putstr_fd("`: not a valid identifier\n", 2);
}

static int	add_new_variable(char *var_name, char *var_value, t_list **env)
{
	t_list	*new_var_env;

	new_var_env = create_new_env_node(var_name, var_value);
	if (!new_var_env)
	{
		write(2, "Error: Failed to export variable\n", 34);
		free(var_name);
		if (var_value)
			free(var_value);
		return (FALSE);
	}
	ft_lstadd_back(env, new_var_env);
	return (TRUE);
}

static void	process_variable(char *arg, t_list **env_list)
{
	char	*var_name;
	char	*var_value;

	// printf("arg: [%s]\n", arg);
	var_name = get_var_name(arg);
	// printf(" var_name: [%s]\n", var_name);
	var_value = get_var_value(arg);
	if (!var_name)
	{
		error_export_syntax(arg);
		free(var_value);
		return ;
	}
	if (!handle_existing_var(var_name, var_value, env_list))
		add_new_variable(var_name, var_value, env_list);
}

/**
 *
 * export abc
 * export abc=123
 * export abc=123  def=456
 */

int	export_variable(t_cmd *curr_cmd, t_mini *mini)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (curr_cmd->cmd_args[i] != NULL)
	{
		if (validate_syntax_name_value(curr_cmd->cmd_args[i]) == 0)
		{
			error_export_syntax(curr_cmd->cmd_args[i]);
			flag = 1;
		}
		else
			process_variable(curr_cmd->cmd_args[i], &(mini->env));
		i ++;
	}
	if (mini->envp_to_array)
		free_string_matrix(mini->envp_to_array);
	mini->envp_to_array = env_list_to_array(mini->env);
	if (!mini->envp_to_array)
	{
		return (1);
	}
	return (flag);
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
