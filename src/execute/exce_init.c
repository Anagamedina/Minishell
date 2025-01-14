
#include "../../includes/minishell.h"

t_pipe	*init_pipe(void)
{
	t_pipe	*pipe_info;

	// Reserva memoria para la estructura t_pipe
	pipe_info = malloc(sizeof(t_pipe));
	if (!pipe_info)
	{
		perror("Error: memoria insuficiente para pipe");
		return (NULL);
	}

	// Crear el pipe actual
	if (pipe(pipe_info->pipe_fds) == -1)
	{
		perror("Error creando pipe");
		free(pipe_info);
		return (NULL);
	}

	pipe_info->in_fd = -1;
	pipe_info->out_fd = -1;
	pipe_info->prev_pipe_fd = -1;         // No hay pipe previo
	pipe_info->last_cmd = 0;
	pipe_info->error_fd = STDERR_FILENO;  // Redirección de errores estándar

	return (pipe_info);
}


t_exec	*init_exec(	char **envp)
{
	t_exec	*exec_info;

	exec_info = malloc(sizeof(t_exec));
	if (!exec_info)
		return NULL;
	exec_info->first_cmd = NULL;
	exec_info->env_vars = lst_to_arr(NULL);
	exec_info->pipe_input_fd = -1;
	exec_info->pipe_output_fd = -1;
	exec_info->cmd_count = 0;
	exec_info->paths = get_path(envp);

	return exec_info;
}