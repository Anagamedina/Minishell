/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:47:46 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/23 17:53:30 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:58:03 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 12:42:42 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cases_builtins(t_mini* mini, t_cmd* curr_cmd)
{
	int	exit_status = -5;

	if (ft_strcmp(curr_cmd->cmd, "pwd") == 0)
		exit_status = ft_pwd(mini);
	else if (ft_strcmp(curr_cmd->cmd, "echo") == 0)
		exit_status = ft_echo(curr_cmd, mini);
	else if (ft_strcmp(curr_cmd->cmd, "export") == 0)
	{
		if (curr_cmd->cmd_args[1])
			exit_status = export_variable(curr_cmd, mini);
		else
		{
			print_export(&mini->env);
			exit_status = 0;
		}

	}
	else if (ft_strcmp(curr_cmd->cmd, "unset") == 0)
		exit_status = ft_unset(&(mini->env), curr_cmd);
	else if (ft_strcmp(curr_cmd->cmd, "env") == 0)
		exit_status = ft_env(mini->env);
	else if (ft_strcmp(curr_cmd->cmd, "cd") == 0)
		exit_status = ft_cd(mini, curr_cmd);
	else if (ft_strcmp(curr_cmd->cmd, "exit") == 0)
	{
		exit_status = builtin_exit(curr_cmd, mini);
		if (exit_status == 255 || exit_status == 0)
			cleanup_and_exit(mini, exit_status);
	}
	return (exit_status);
}



/*
int	cases_builtins(t_mini* mini, t_cmd* curr_cmd)
{
	int	exit_status;

	exit_status = -1;
	if (ft_strcmp(curr_cmd->cmd, "pwd") == 0)
	{
		return (ft_pwd(mini));
	}
	if (ft_strcmp(curr_cmd->cmd, "echo") == 0)
	{
		return (ft_echo(curr_cmd, mini));
	}
	if (ft_strcmp(curr_cmd->cmd, "export") == 0)
	{
		if (curr_cmd->cmd_args[1] != NULL)
			return (export_variable(curr_cmd, mini));
		else
		{
			print_export(&mini->env);
			return (0);
		}
	}
	if (ft_strcmp(curr_cmd->cmd, "unset") == 0)
	{
		return (ft_unset(&(mini->env), curr_cmd));
	}
	if (ft_strcmp(curr_cmd->cmd, "env") == 0)
	{
		return (print_env_list(mini->env));
	}
	if (ft_strcmp(curr_cmd->cmd, "cd") == 0)
	{
		return (ft_cd(mini, curr_cmd));
	}
	else if (ft_strcmp(curr_cmd->cmd, "exit") == 0)
	{
		exit_status = builtin_exit(curr_cmd, mini);
		if (exit_status == 255 || exit_status == 1)
		{
			cleanup_and_exit(mini, mini->exit_status);
		}
		return (exit_status);
	}
	return (0);
}*/




/*
char	*expand_exit_status(t_mini *mini, char *str)
{
	char *tmp;

	if (!str || !mini)  // ✅ Verifica que mini y str no sean NULL
		return (NULL);
	tmp = NULL;
	if (ft_strchr(str, '$'))
	{
		if (ft_strcmp(str, "$?") == 0)
		{
			tmp = ft_itoa(mini->exit_status);  // ✅ Verifica que mini->exit_status es accesible
			if (!tmp)
				return (ft_strdup(""));  // ✅ Retorna "" si ft_itoa falla
			return (tmp);
		}
	}
	return (ft_strdup(str));  // ✅ Devuelve siempre una cadena válida
}

int	ft_echo(t_cmd *cmd, t_mini* mini)
{
	int	i;
	int	no_newline;
	char *expanded_arg;

	i = 1;
	no_newline = 0;
	while (cmd->cmd_args[i] && ft_strcmp(cmd->cmd_args[i], "-n") == 0)
	{
		no_newline = 1;
		i++;
	}
	while (cmd->cmd_args[i])
	{
		expanded_arg = expand_exit_status(mini, cmd->cmd_args[i]);
		if (expanded_arg)
		{
			printf("%s", expanded_arg);
			free(expanded_arg);
		}
		if (cmd->cmd_args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}

void	execute_builtin_or_external(t_cmd *curr_cmd, t_mini *mini)
{
	int	exit_status_last_command;

	exit_status_last_command = 0;
	if (curr_cmd->is_builtin == 1)
	{
		exit_status_last_command = cases_builtins(mini, curr_cmd);
		mini->exit_status = exit_status_last_command;  // ✅ Solo actualiza el exit status, no hace `exit()`
		return;  // ✅ No cierra el shell en built-ins
	}
	if (curr_cmd->is_external == 1)
	{
		execute_external(curr_cmd, mini->envp_to_array);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}
*/
