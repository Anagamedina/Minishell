/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:06:30 by catalinab         #+#    #+#             */
/*   Updated: 2025/01/17 16:05:48 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

	// Inicializar los descriptores de archivos
	pipe_info->prev_pipe_fd = -1;         // No hay pipe previo
	pipe_info->last_cmd = 0;
	pipe_info->error_fd = STDERR_FILENO;  // Redirección de errores estándar

	// Inicializar los descriptores del pipe actual a -1 (sin pipe creado aún)
	pipe_info->pipe_fds[0] = -1;
	pipe_info->pipe_fds[1] = -1;

	return (pipe_info);
}


t_exec	*init_exec(t_list *env_list)
{
	t_exec	*exec_info;

	exec_info = malloc(sizeof(t_exec));
	if (!exec_info)
		return NULL;
	exec_info->first_cmd = NULL;
	exec_info->env_vars = lst_to_arr(env_list);
	exec_info->pipe_input_fd = -1;
	exec_info->pipe_output_fd = -1;
	exec_info->cmd_count = 0;
	exec_info->paths = get_path(exec_info->env_vars);

	return exec_info;
}



/*// Initialize the first pipe
t_pipe *pipe_info = init_pipe();
if (!pipe_info) {
    return;  // Manejar el error de memoria insuficiente
}

// Lista de comandos
t_list *current = mini->exec->first_cmd;
int input_fd = -1;

while (current)
{
    t_cmd *cmd = (t_cmd *)current->content;

    if (current->next)
    {
        pipe_info = create_pipe(0);  // Crea un nuevo pipe para el siguiente comando
        if (!pipe_info)
        {
            perror("Error creando pipe");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        pipe_info->out_fd = -1;  // Si es el último comando, ya no tiene salida
    }

    cmd->input_fd = input_fd;
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Error creando proceso hijo");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        setup_pipes(pipe_info, cmd->cmd_id);  // Configura las redirecciones para este proceso
        execute_external(cmd, lst_to_arr(mini->env));  // Ejecuta el comando externo o builtin
        exit(EXIT_SUCCESS);  // Se asegura de que el proceso hijo termine
    }
    else
    {
        if (cmd->input_fd != -1) {
            close(cmd->input_fd);  // Cierra el descriptor de entrada del proceso anterior
        }
        if (pipe_info->out_fd != -1) {
            close(pipe_info->out_fd);  // Cierra el descriptor de salida del pipe
        }
        input_fd = pipe_info->pipe_fds[0];  // Establece el nuevo input para el siguiente comando
        waitpid(pid, NULL, 0);  // Espera al proceso hijo
    }

    current = current->next;  // Avanza al siguiente comando
}*/