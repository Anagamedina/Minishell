/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:55:27 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/28 12:24:37 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_export_syntax(char *var_name)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(var_name, 2);
	ft_putendl_fd("`: not a valid identifier", 2);
}

static char	*get_var_name_append(char *arg)
{
	int		i;
	char	*var_name;

	i = 0;
	while (arg[i] && arg[i] != '+' && arg[i] != '=')
		i++;
	var_name = ft_substr(arg, 0, i);
	return (var_name);
}

static char	*get_var_value_append(char *arg)
{
	char	*value_start;
	char	*var_value;

	value_start = ft_strchr(arg, '=');
	if (!value_start)
		return (NULL);
	var_value = ft_strdup(value_start + 1);
	return (var_value);
}

static void	add_or_update_env_variable(t_list **env_list, char *arg)
{
	char	*var_name;
	char	*var_value;
	int		append_flag;

	append_flag = 0;
	var_name = get_var_name(arg);
	if (ft_strnstr(arg, "+=", ft_strlen(arg)) != NULL)
	{
		append_flag = 1;
		var_name = get_var_name_append(arg);
		var_value = get_var_value_append(arg);
	}
	var_value = get_var_value(arg);
	if (!var_name)
	{
		error_export_syntax(arg);
		free(var_value);
		return ;
	}
	if (!ft_strchr(arg, '='))
		var_value = NULL;
	if (!update_env_var_exist(env_list, var_name, var_value, append_flag))
		add_new_env_variable(env_list, var_name, var_value);
}

int	ft_export(t_cmd *curr_cmd, t_mini *mini)
{
	int	i;
	int	error_flag;

	error_flag = 0;
	i = 1;
	while (curr_cmd->cmd_args[i] != NULL)
	{
		if (validate_syntax_name_value(curr_cmd->cmd_args[i]) == FALSE)
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
