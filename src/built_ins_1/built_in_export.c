/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:55:27 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/14 21:15:22 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_export_syntax(char *var_name)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(var_name, 2);
	ft_putendl_fd("`: not a valid identifier", 2);
}

static int	handle_append_case(char **var_name, char **var_value, char *arg)
{
	char	*temp;

	temp = *var_name;
	*var_name = get_var_name_append(arg);
	free(temp);
	if (*var_value)
		free(*var_value);
	*var_value = get_var_value_append(arg);
	return (1);
}

static int	extract_env_var(char *arg, char **var_name, char **var_value)
{
	int	append_flag;

	append_flag = 0;
	*var_value = NULL;
	*var_name = get_var_name(arg);
	if (!*var_name)
		return (error_export_syntax(arg), 0);
	if (ft_strnstr(arg, "+=", ft_strlen(arg)) != NULL)
		append_flag = handle_append_case(var_name, var_value, arg);
	else
		*var_value = get_var_value(arg);
	if (!*var_name)
		return (free(*var_value), 0);
	if (!ft_strchr(arg, '='))
		return (free(*var_value), *var_value = NULL, append_flag);
	return (append_flag);
}

static void	add_or_update_env_variable(t_list **env_list, char *arg)
{
	char	*var_name;
	char	*var_value;
	int		append_flag;
	int		updated;

	append_flag = extract_env_var(arg, &var_name, &var_value);
	if (!var_name)
	{
		free(var_value);
		return ;
	}
	updated = update_env_var(env_list, var_name, var_value, append_flag);
	if (!updated)
		add_new_env_variable(env_list, var_name, var_value);
	else
	{
		var_value = NULL;
	}
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
	mini->envp_to_array = NULL;
	mini->envp_to_array = env_list_to_array(mini->env);
	if (!mini->envp_to_array)
		return (1);
	return (error_flag);
}
