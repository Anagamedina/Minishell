

#include "../../includes/minishell.h"
//paths[0] = "/usr/local/bin"
//full_path = "/usr/local/bin/"
// cmd_path =  "/usr/local/bin/ls"

char	*get_cmd_path(char *cmd, char **paths)
{
	char	*cmd_path;
	char	*full_path;
	int		i;

	if (cmd == NULL) return NULL;
	// Retorna una copia del comando si es válido
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (paths && paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	// print_paths(&cmd_path);
	return (NULL);
}

t_cmd	*handle_cmd_error(t_cmd *new)
{
	perror("Error: Command not found here!!");
	free_split_result(new->cmd_args);
	free(new);
	return (NULL);
}


// // Obtiene las rutas en PATH del entorno
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


 