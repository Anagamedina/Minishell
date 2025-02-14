/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:48:37 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/14 14:43:18 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"
/* Función que maneja la ejecución de los comandos builtins
static void execute_builtin(t_cmd *cmd, t_mini *mini)
{
	if (strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (strcmp(cmd->cmd, "cd") == 0)
		ft_cd(cmd, mini);
	else if (strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (strcmp(cmd->cmd, "export") == 0)
		ft_export(cmd, mini);
	else if (strcmp(cmd->cmd, "unset") == 0)
		ft_unset(cmd, mini);
	else if (strcmp(cmd->cmd, "env") == 0)
		ft_env(mini);
	else if (strcmp(cmd->cmd, "exit") == 0)
		ft_exit(cmd);
}*/

static int	count_env_variables(t_list *env_list)
{
	t_list	*curr_node;
	int		env_count;

	curr_node = env_list;
	env_count = 0;
	while (curr_node)
	{
		env_count ++;
		curr_node = curr_node->next;
	}
	return (env_count);
}

void	free_env_array(char **env_array, int allocated)
{
	while (allocated > 0)
	{
		free(env_array[allocated]);
		allocated--;
	}
	free(env_array);
}

char	**env_list_to_array(t_list *env_list)
{
	t_list	*curr_node;
	t_env	*curr_env_var;
	char	**env_array;
	int		env_count;
	int		i;

	env_count = count_env_variables(env_list);
	env_array = ft_calloc(env_count + 1, sizeof(char *));
	if (!env_array)
	{
		perror("Error: cant assign memory to env_list_to_array");
		return (NULL);
	}
	curr_node = env_list;
	i = 0;
	while (i < env_count)
	{
		curr_env_var = (t_env *)curr_node->content;
		env_array[i] = ft_strdup(curr_env_var->full_var);
		if (!env_array[i])
		{
			perror("Error: No se pudo duplicar variable de entorno");
			free_env_array(env_array, i);
			return (NULL);
		}
		curr_node = curr_node->next;
		i ++;
	}
	env_array[env_count] = NULL;
	return (env_array);
}
