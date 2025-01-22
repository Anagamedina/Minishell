/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/17 17:48:05 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"

char	*get_cmd_path(t_tokens *token, char **paths)
{
	char		*cmd_path;
	char		*full_path;
	int 		i;

	if (access(token->str, X_OK) == 0)
		return ft_strdup(token->str);

	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(full_path, token->str);
		free(full_path);

		if (access(cmd_path, X_OK) == 0)
			return cmd_path;
		free(cmd_path);
		i++;
	}
	return (NULL);
}

//char **paths = { "/usr/bin", "/bin", "/usr/local/bin", NULL };
char	**get_path(char **env)
{
	char	**paths;
	char	*path_var;
	int		i;

	paths = NULL;
	path_var = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_var = ft_strdup(env[i] + 5);
			break ;
		}
		i++;
	}
	if (path_var)
	{
		paths = ft_split(path_var, ':');
		free(path_var);
		if (!paths)
		{
			perror("Error: No se pudo dividir PATH en subrutas");
			return (NULL);
		}
	}
	return (paths);
}