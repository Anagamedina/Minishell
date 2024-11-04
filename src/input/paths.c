
#include "../../includes/minishell.h"

char	*get_cmd_path(char *cmd, char **paths)
{
	char	*cmd_path;
	char	*full_path;
	int		i;

	// Retorna una copia del comando si es válido
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

t_cmd	*handle_cmd_error(t_cmd *new)
{
	perror("Error: Command not found here!!");
	free_split_result(new->cmd_args);
	free(new);
	return (NULL);
}
