
#include "../../includes/minishell.h"

/*
t_exec *init_exec(void)
{
	t_exec *exec = NULL;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);

	exec->path = NULL;
	exec->env_vars = NULL;
	exec->pipe_input_fd = -1;
	exec->pipe_output_fd = -1;
	exec->first_cmd = NULL;
	exec->cmd_count = 0;
	//exec->exit_status = 0;

	//exec->error = 0;

	return (exec);
}

t_list *init_exec_list(void)
{

}*/





t_exec *init_exec(char **argv, char **env, int argc) {
	t_exec *exec;

	// Asignación de memoria para la estructura t_exec
	exec = malloc(sizeof(t_exec));
	if (!exec) {
		perror("Error: malloc failed for t_exec");
		return NULL;
	}

	// Inicialización de la lista de variables de entorno (suponiendo que tienes una función init_env_list)
	exec->env_vars = init_env_list(env);
	if (!exec->env_vars) {
		free(exec);
		perror("Error: failed to initialize environment variables");
		return NULL;
	}

	// Obtener las rutas de búsqueda para los comandos
	exec->paths = get_path(env);
	if (!exec->paths) {
		free(exec);
		perror("Error: failed to get paths from environment");
		return NULL;
	}

	// Inicialización del contador de comandos
	exec->cmd_count = argc - 1;

	// Crear la lista de comandos (asumiendo que tienes una función create_cmd_list)
	exec->first_cmd = create_cmd_list(argv, exec->paths, exec->cmd_count);
	if (!exec->first_cmd) {
		free(exec->env_vars);  // Asegúrate de liberar la lista de env si algo falla
		free(exec->paths);     // Liberar las rutas obtenidas
		free(exec);
		perror("Error: failed to create command list");
		return NULL;
	}

	// Inicializar los descriptores de archivos para el pipe
	exec->pipe_input_fd = -1; // No hay pipe de entrada por defecto
	exec->pipe_output_fd = -1; // No hay pipe de salida por defecto

	return exec;
}