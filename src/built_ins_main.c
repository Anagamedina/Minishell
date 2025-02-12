/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:45:57 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/12 11:21:48 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/06 12:55:18 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cases_builtins(t_mini *mini)
{
	t_cmd	*curr_cmd;

	curr_cmd = (t_cmd *)mini->exec->first_cmd->content;
	if (ft_strcmp(curr_cmd->cmd, "echo") == 0)
	{
		ft_echo(curr_cmd);
	}
	else if (ft_strcmp(curr_cmd->cmd, "export") == 0)
	{
		if (curr_cmd->cmd_args[1] == NULL)
			print_export(&mini->env);
		else
		{
			export_variable(curr_cmd, &(mini->env));
			printf("--------------PRINT ENV LIST---------------------------\n");
			print_env_list(mini->env);
			printf("\n-----------------------------------------\n");
		}
	}
	else if (ft_strcmp(curr_cmd->cmd, "unset") == 0)
	{
		// TODO: update unset function
	}
	else if (ft_strcmp(curr_cmd->cmd, "env") == 0)
		print_env_list(mini->env);
}

/*
int	set_env(t_list **env_list, char *key, char *value)
{
	t_list	*current_node;
	t_env	*current_env;

	if (!key || !env_list)
		return (1);

	current_node = *env_list;
	while (current_node)
	{
		current_env = (t_env *)current_node->content;
		if (ft_strcmp(key, current_env->key) == 0) // Si la variable ya existe
		{
			free(current_env->value);
			current_env->value = value ? ft_strdup(value) : ft_strdup("");
			return (0);
		}
		current_node = current_node->next;
	}

	// Si la variable no existe, la creamos
	// t_env *new_env = init_env_var(key, value);
	char	*tmp =  ft_strjoin(key, "=");
	// t_env	*new_env = create_new_env_node(ft_strjoin(tmp, value), key, value);
	// if (!new_env)
	// 	return (1);
	// ft_lstadd_back(env_list, ft_lstnew(new_env));

	return (0);
}
*/
/*
    if ((ft_strcmp((char *)current_command->cmd, "export") == 0))
    {
		builtin_export(mini);
    }
    else if (ft_strcmp((char *)current_command->cmd, "cd") == 0)
	{
		printf("enmtra caso cd\n");
		get_current_directory(mini);
	}
*/
