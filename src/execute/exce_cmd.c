/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/07 17:20:14 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_external(t_cmd *cmd, char **envp)
{
	execve(cmd->cmd_path, cmd->cmd_args, envp);
	perror("Error ejecutando comando externo con execve");
	exit(EXIT_FAILURE);
}

//funcion en la parte de gestion del padre donde haya redirecciones
static void	set_redis(t_cmd *curr_cmd)
{
	int p_empty_fd[2];

	if (curr_cmd->redir_list != NULL)
	{
	// SI EL COMANDO NO TIENE ENTRADA, ASIGNAR UN `STDIN` VACÍO
		if (curr_cmd->input_fd == STDIN_FILENO)
		{
			if (pipe(p_empty_fd) == -1)
			{
				perror("Error creando pipe vacío");
				exit(EXIT_FAILURE);
			}
			curr_cmd->input_fd = p_empty_fd[0];
			close(p_empty_fd[1]);
		}
	}
}

//gestion del padre cuando no hay redirecciones
static void setup_fds(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
    // Si no es el último comando, crear una pipe
    if (!curr_cmd->last_cmd)
    {
        if (pipe(pipe_fd) == -1)
        {
            perror("Error creando pipe");
            exit(EXIT_FAILURE);
        }
        curr_cmd->output_fd = pipe_fd[1]; // Asignar salida a la pipe
    }
    else
    {
        curr_cmd->output_fd = STDOUT_FILENO; // Último comando: salida a STDOUT
    }

    // Asignar la entrada del comando
    curr_cmd->input_fd = *input_fd;
}

void handle_child(t_cmd *curr_cmd, t_mini *mini)
{
    // Redirigir entrada si no es el primer comando
    if (curr_cmd->input_fd != STDIN_FILENO)
    {
        if (dup2(curr_cmd->input_fd, STDIN_FILENO) == -1)
        {
            perror("Error redirigiendo entrada");
            exit(EXIT_FAILURE);
        }
        close(curr_cmd->input_fd);
    }

    // Redirigir salida si no es el último comando
    if (curr_cmd->output_fd != STDOUT_FILENO)
    {
        if (dup2(curr_cmd->output_fd, STDOUT_FILENO) == -1)
        {
            perror("Error redirigiendo salida");
            exit(EXIT_FAILURE);
        }
    	close(curr_cmd->output_fd);
        // close(pipe_fd[1]); // Cerrar extremo de escritura de la pipe
    }

    // Convertir variables de entorno a array
    char **envp = lst_to_arr(mini->env);

    // Ejecutar el comando
    if (curr_cmd->is_external == 1)
    {
        execute_external(curr_cmd, envp);
    }
    else if (curr_cmd->is_builtin == 1)
    {
        cases_builtins(mini);
    }

    exit(EXIT_FAILURE); // Si llega aquí, algo falló
}

static void handle_parent(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
    // Cerrar el extremo de escritura en el padre si no es el último comando
    if (curr_cmd->output_fd != STDOUT_FILENO)
    {
    	close(curr_cmd->output_fd);
        // close(pipe_fd[1]);
    }

    // Cerrar el extremo de lectura anterior si no es STDIN
    if (curr_cmd->input_fd != STDIN_FILENO)
    {
        close(curr_cmd->input_fd);
    }

    // Actualizar `input_fd` para el siguiente comando
    *input_fd = pipe_fd[0];
}

static void wait_for_children(int num_children)
{
    while (num_children > 0)
    {
        if (wait(NULL) == -1)
        {
            perror("Error esperando proceso hijo");
        }
        else
        {
            num_children--;
        }
    }
}

int execute_commands(t_mini *mini)
{
    t_list *t_list_exec_cmd = mini->exec->first_cmd;
    t_cmd  *curr_cmd;
    pid_t  pid;
    int    input_fd = STDIN_FILENO;
    int    pipe_fd[2];
    int    i = 0;
    int    len_t_list_exec_cmd = ft_lstsize(t_list_exec_cmd);

    while (t_list_exec_cmd)
    {
        curr_cmd = (t_cmd *)t_list_exec_cmd->content;
        curr_cmd->cmd_id = i++;

    		//&& curr_cmd->input_fd != STDIN_FILENO)
    	if (apply_redirections(curr_cmd) >= 1)
    	{
    		curr_cmd->input_fd = input_fd;
    		set_redis(curr_cmd);
    	}
    	else
    		setup_fds(curr_cmd, pipe_fd, &input_fd);
    	//printf("input_fd: %d\n", input_fd);
        // Crear un proceso hijo
        pid = fork();
        if (pid < 0)
        {
            perror("Error creando proceso hijo");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Proceso hijo
            handle_child(curr_cmd, mini);
        }
        else
        {
            // Proceso padre
            handle_parent(curr_cmd, pipe_fd, &input_fd);
        }

        t_list_exec_cmd = t_list_exec_cmd->next;
    }

    // Cerrar cualquier descriptor restante en el padre
    if (input_fd != STDIN_FILENO)
    {
        close(input_fd);
    }

    // Esperar a que terminen los hijos
    wait_for_children(len_t_list_exec_cmd);

    return (TRUE);
}
