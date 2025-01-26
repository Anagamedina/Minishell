/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:48:37 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/26 00:45:41 by dasalaza         ###   ########.fr       */
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

char	**lst_to_arr(t_list *env_list)
{
	t_list	*node;
	t_env	*current;
	char	**arr;
	int		count = 0;

	node = env_list;
	while (node)
	{
		count++;
		node = node->next;
	}

	arr = ft_calloc(count + 1, sizeof(char *)); // +1 para NULL final
	if (!arr)
		return NULL;
	node = env_list;
	count = 0;
	while (node)
	{
		current = (t_env *)node->content;
		arr[count] = ft_strdup(current->full_var);
		if (!arr[count])
		{
			while (count > 0)
				free(arr[--count]);
			free(arr);
			return NULL;
		}
		count++;
		node = node->next;
	}
	arr[count] = NULL; // Terminar el array con NULL
	return arr;
}
