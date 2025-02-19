/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:58:03 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/19 20:49:44 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:04:01 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/19 10:12:51 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * update the value of an existing variable in the environment list.
 * @param var_name: name of the variable to update.
 * @param new_value: new value to assign to the variable.
 * @param env_list: pointer to the environment list.
 * @return 1 if the variable was updated, 0 otherwise.
 */

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
			return (1);
		current_node = current_node->next;
	}
	return (FALSE);
}

// TODO: hacerlo en un loop dado que es posible agregar mas de una variable
/**
 *
 * export abc
 * export abc=123
 * export abc=123  def=456
 *
 * @param curr_cmd
 * @param mini
 */
void	export_variable(t_cmd *curr_cmd, t_mini *mini)
{
	char	*var_name;
	char	*var_value;
	t_list	*new_var_env;

	if (!curr_cmd->cmd_args[1])
		return ;
	if (validate_syntax_name_value(curr_cmd->cmd_args[1]) == FALSE)
	{
		write(2, "export: invalid syntax\n", 24);
		return ;
	}
	var_name = get_var_name(curr_cmd->cmd_args[1]);
	var_value = get_var_value(curr_cmd->cmd_args[1]);
	if (!var_name)
	{
		write(2, "export: invalid variable name\n", 31);
		return ;
	}
	if (update_var_exist(var_name, var_value, &(mini->env)) == TRUE)
	{
		free(var_name);
		free(var_value);
		return ;
	}
	new_var_env = create_new_env_node(var_name, var_value);
	if (!new_var_env)
	{
		write(2, "Error: Failed to export variable\n", 34);
		free(var_name);
		free(var_value);
		return ;
	}
	ft_lstadd_back(&(mini->env), new_var_env);
	if (mini->envp_to_array)
		free_string_matrix(mini->envp_to_array);
	mini->envp_to_array = env_list_to_array(mini->env);
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
