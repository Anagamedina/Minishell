/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:14:26 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/03 21:49:36 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_env_variables(t_list *env_list)
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

	if (!env_list)
		return (NULL);
	env_count = count_env_variables(env_list);
	env_array = ft_calloc(env_count + 1, sizeof(char *));
	if (!env_array)
	{
		perror("Error: cant assign memory to env_list_to_array");
		return (NULL);
	}
	curr_node = env_list;
	i = 0;
	while (curr_node && i < env_count)
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

int	is_builtin_command(char *cmd)
{
	return (ft_strcmp(cmd, ECHO_VAR) == 0 || ft_strcmp(cmd, EXPORT) == 0 || \
		ft_strcmp(cmd, UNSET) == 0 || ft_strcmp(cmd, ENV) == 0 || \
		ft_strcmp(cmd, CD) == 0 || ft_strcmp(cmd, PWD) == 0 || \
		ft_strcmp(cmd, EXIT) == 0);
}


char	*is_cmd_external(t_mini *mini, t_tokens *token)
{
	char		**paths;
	char		*cmd_path;

	if (!mini || !mini->tokens)
		return (NULL);
	paths = get_path(mini->envp_to_array);
	cmd_path = get_cmd_path(token, paths);
	return (cmd_path);
}
