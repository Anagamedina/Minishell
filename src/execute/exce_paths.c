/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:12:52 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/08 00:13:45 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* -------------------------------------------------------------------------- */
/*  get_cmd_path: resuelve ruta ejecutable combinando PATH + token            */
/* -------------------------------------------------------------------------- */
char	*get_cmd_path(t_tokens *token, char **paths)
{
	char		*cmd_path;
	char		*full_path;
	int			i;

	if (ft_strcmp(token->str, ".") == 0 || ft_strcmp(token->str, "..") == 0 \
			|| ft_strncmp(token->str, "../", 3) == 0)
		return (NULL);
	if (token->str[0] == '/' || token->str[0] == '.')
	{
		if (access(token->str, X_OK) == 0)
			return (ft_strdup(token->str));
		return (NULL);
	}
	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(full_path, token->str);
		free(full_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

/*char	**get_path(char **env)
{
	char	**paths;
	char	*path_var;
	int		i;

	paths = NULL;
	path_var = NULL;
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_var = ft_strdup(env[i] + 5);
			if (!path_var)
				return (NULL);
			break ;
		}
		i ++;
	}
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	free(path_var);
	if (!paths)
	{
		perror("Error: Cant assign memory to paths.");
		return (NULL);
	}
	return (paths);
}*/

/* -------------------------------------------------------------------------- */
/*  extract_path_variable: extrae valor de PATH del entorno                   */
/* -------------------------------------------------------------------------- */
char	*extract_path_variable(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}

/* -------------------------------------------------------------------------- */
/*  get_path: divide PATH en una matriz de rutas                              */
/* -------------------------------------------------------------------------- */
char	**get_path(char **env)
{
	char	**paths;
	char	*path_var;

	paths = NULL;
	path_var = extract_path_variable(env);
	if (path_var)
	{
		paths = ft_split(path_var, ':');
		free(path_var);
		if (!paths)
			return (NULL);
	}
	else
		return (NULL);
	return (paths);
}
