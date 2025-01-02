
#include "../../includes/minishell.h"

//execve(cmd_path, cmd_args, exec_info->env_vars);

t_exec *init_exec(char **envp)
{
	t_exec *exec_info;

	// Asignar memoria para la estructura t_exec
	exec_info = malloc(sizeof(t_exec));
	if (!exec_info)
		return NULL;

	exec_info->first_cmd = NULL;
	//exec_info->env_vars = lst_to_arr(NULL, envp);
	exec_info->pipe_input_fd = -1;
	exec_info->pipe_output_fd = -1;
	exec_info->cmd_count = 0;
	exec_info->paths = get_path(envp);

	return exec_info;
}


/*static void execute_external(t_cmd *cmd, char **paths, t_mini *mini)
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
}*/