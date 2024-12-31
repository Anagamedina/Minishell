
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
/* Función que maneja la ejecución de comandos externos */
static void execute_external(t_cmd *cmd, char **paths, t_mini *mini)
{
	char    *path;
	char    **env;
	int     i;

	i = 0;
	env = init_env_list(mini->env);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd->cmd);
		if (access(path, X_OK) == 0)
		{
			execve(path, cmd->cmd_args, env);
			free(path);
			return;
		}
		free(path);
		i++;
	}
	// Si llegamos aquí, significa que no encontramos el comando
	ft_putstr_fd(cmd->cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127); // Error de comando no encontrado
}

/* Función principal para ejecutar comandos */
void exec_command(t_cmd *cmd, t_mini *mini)
{
	pid_t pid;
	char **paths;

	paths = get_path(mini->env);
	if (cmd->is_builtin)
	{
		printf("Es un builtin\n");
		//execute_builtin(cmd, mini);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			exit(1);
		}
		if (pid == 0)
		{

			execute_external(cmd, paths, mini);
		}
		else
		{
			waitpid(pid, &cmd->exit_code, 0);
			free(paths);
		}
	}
}