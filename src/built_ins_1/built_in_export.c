/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:53:35 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/18 10:32:59 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Maneja el caso donde el primer token es "export".
 * Puede listar variables de entorno o agregar/modificar una.
 * caso 01:
 * line = export key=value
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

// TODO: refactorize this function
char	*ft_strjoin_export(char *s1, char *s2, char c)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	result = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	result[i++] = c;
	j = 0;
	while (j < len2)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}
