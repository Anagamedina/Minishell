
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


char **lst_to_arr(t_list *lst, char **envp)
{
	t_list *current = lst;
	int count = 0;
	char **arr;

	// Si la lista está vacía, simplemente la convertimos a un array vacío
	if (!lst)
	{
		// Contamos los elementos en envp
		while (envp[count])
			count++;

		// Reservamos memoria para el array de cadenas
		arr = ft_calloc( count + 1, sizeof(char *)); // +1 para el NULL final
		if (!arr)
			return NULL;

		// Copiamos las variables de entorno desde envp al nuevo array
		current = lst;
		while (envp[count])
		{
			arr[count] = ft_strdup(envp[count]); // Copiar la cadena
			count++;
		}

		arr[count] = NULL;  // Terminamos el array con NULL
		return arr;
	}

	// Si tenemos una lista enlazada, contamos los elementos de la lista
	current = lst;
	while (current)
	{
		count++;
		current = current->next;
	}

	// Reservamos memoria para el array de cadenas
	arr = ft_calloc( count + 1, sizeof(char *)); // +1 para el NULL final
	if (!arr)
		return NULL;

	// Copiamos las cadenas de la lista enlazada al array
	current = lst;
	count = 0;
	while (current)
	{
		arr[count] = ft_strdup(((t_env *)current->content)->full_var); // Copiar la cadena de cada nodo
		current = current->next;
		count++;
	}

	arr[count] = NULL;

	return arr;
}

t_exec *init_exec(char **envp)
{
	t_exec *exec_info;

	// Asignar memoria para la estructura t_exec
	exec_info = malloc(sizeof(t_exec));
	if (!exec_info)
		return NULL;

	exec_info->first_cmd = NULL;
	exec_info->env_vars = lst_to_arr(NULL, envp);
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