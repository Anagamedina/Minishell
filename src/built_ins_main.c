/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:58:03 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/21 22:46:54 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	unset_variable(t_list **env_list, char *var_name)
{
	t_list	*current;
	t_list	*prev;
	t_env	*env_var;

	if (!env_list || !*env_list || !var_name)
		return ;
	current = *env_list;
	prev = NULL;
	while (current)
	{
		env_var = (t_env *) current->content;
		if (ft_strcmp(env_var->key, var_name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free_env(env_var);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	cases_builtins(t_mini *mini, t_cmd *curr_cmd)
{
	int		i;

	i = 0;
	if (ft_strcmp(curr_cmd->cmd, "pwd") == 0)
	{
		ft_pwd(mini);
	}
	else if (ft_strcmp(curr_cmd->cmd, "echo") == 0)
		ft_echo(curr_cmd);
	else if (ft_strcmp(curr_cmd->cmd, "export") == 0)
	{
		/*
		i = 0;
		printf("----------------------------------------\n");
		while (curr_cmd->cmd_args[i] != NULL)
		{
			printf("arg[%d]: [%s]\n", i, curr_cmd->cmd_args[i]);
			i ++;
		}
		printf("----------------------------------------\n");
		*/
		if (curr_cmd->cmd_args[1] != NULL)
			export_variable(curr_cmd, mini);
		else
			print_export(&mini->env);
	}
	else if (ft_strcmp(curr_cmd->cmd, "unset") == 0)
	{
		i = 0;
		while (curr_cmd->cmd_args[i] != NULL)
		{
			unset_variable(&(mini->env), curr_cmd->cmd_args[i]);
			i ++;
		}
	}
	else if (ft_strcmp(curr_cmd->cmd, "env") == 0)
	{
		print_env_list(mini->env);
	}
	else if (ft_strcmp(curr_cmd->cmd, "cd") == 0)
	{
		ft_cd(mini, curr_cmd);
	}
	else if (ft_strcmp(curr_cmd->cmd, "exit") == 0)
	{
		builtin_exit(curr_cmd, mini);
	}
}