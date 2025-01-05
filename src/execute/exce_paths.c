

#include "../../includes/minishell.h"
//paths[0] = "/usr/local/bin"
//full_path = "/usr/local/bin/"
// cmd_path =  "/usr/local/bin/ls"
/*Recibe el nombre del comando (cmd) y las rutas (paths)donde debe buscarlo.
-Forma la ruta completa para el comando combinando la ruta del directorio con el comando.
-Verifica si el archivo existe y es ejecutable usando funciones como access o stat.*/


char	*get_cmd_path(t_tokens *token, char **paths)
{
	char		*cmd_path;
	char		*full_path;
	int 		i;

	// Retorna una copia del comando si es válido
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