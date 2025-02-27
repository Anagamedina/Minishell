/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:59:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/27 17:44:43 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
static void	update_last_executed_command(t_list **env_list, char *last_cmd)
{
	if (!last_cmd)
		return ;
	// Actualizar la variable `_` con el último comando ejecutado
	set_variable_in_env_list(env_list, "_", last_cmd);
}
*/

t_mini	*init_mini_list(char **envp)
{
	t_mini	*minishell;
	char	*shlvl;

	minishell = malloc(sizeof(t_mini));
	if (!minishell)
		return (NULL);
	minishell->bash_lvl = -1;
	minishell->chars_in_line = -1;
	minishell->env = init_env_list(envp);
	if (!minishell->env)
		return (NULL);
	minishell->envp_to_array = env_list_to_array(minishell->env);
	if (minishell->env == NULL)
	{
		free(minishell);
		return (NULL);
	}
	minishell->tokens = NULL;
	minishell->exec = NULL;
	minishell->exit_status = 0;
	shlvl = get_variable_in_env_list(minishell->env, SHLVL);
	configure_shell_env(&minishell->env, shlvl);
	return (minishell);
}
