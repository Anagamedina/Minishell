/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/06 14:07:17 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	execute_external(t_cmd *cmd, char **envp)
{
	execve(cmd->cmd_path, cmd->cmd_args, envp);
	perror("Error ejecutando comando externo con execve");
	exit(EXIT_FAILURE);
}

int	execute_commands(t_mini *mini)
{
	t_list	*t_list_exec_cmd;
	t_cmd	*curr_cmd;
	pid_t	pid;
	int		input_fd;
	int		pipe_fd[2];
	int		i;
	int		len_t_list_exec_cmd;
	int		counter_external_commands = 0;

	t_list_exec_cmd = mini->exec->first_cmd;
	input_fd = STDIN_FILENO;
	i = 0;
	len_t_list_exec_cmd = ft_lstsize(t_list_exec_cmd);

	// RECORRER LA LISTA DE COMANDOS
	while (t_list_exec_cmd)
	{
		curr_cmd = (t_cmd *)t_list_exec_cmd->content;
		curr_cmd->cmd_id = i++;

		char **envp = lst_to_arr(mini->env);
		if (curr_cmd->is_builtin == 1)
		{
			// TODO: Replicar pipes para que funciones el caso "echo hello > output.txt".
			// if (apply_redirections(curr_cmd) == TRUE && curr_cmd->input_fd != STDIN_FILENO)
				// curr_cmd->input_fd = input_fd;
			cases_builtins(mini);
		}
		else if (curr_cmd->is_external == 1)
		{
			counter_external_commands += 1;
			// APLICAR REDIRECCIONES SI EXISTEN
			if (apply_redirections(curr_cmd) == TRUE && curr_cmd->input_fd != STDIN_FILENO)
				curr_cmd->input_fd = input_fd;
			// GESTIONAR PIPES SI HAY MÁS COMANDOS
			if (t_list_exec_cmd->next)
			{
				// SI HAY REDIRECCIÓN DE SALIDA (>) NO SE CREA UN PIPE
				if (curr_cmd->redir_list != NULL)
				{
					// SI EL COMANDO NO TIENE ENTRADA, ASIGNAR UN `STDIN` VACÍO
					if (curr_cmd->input_fd == STDIN_FILENO)
					{
						int p_empty_fd[2];

						if (pipe(p_empty_fd) == -1)
						{
							perror("Error creando pipe vacío");
							exit(EXIT_FAILURE);
						}
						curr_cmd->input_fd = p_empty_fd[0];
						close(p_empty_fd[1]);
						
					}
				}
				else
				{
					// CREAR UN PIPE NORMAL SI NO HAY REDIRECCIÓN DE SALIDA
					if (pipe(pipe_fd) == -1)
					{
						perror("Error creando pipe");
						exit(EXIT_FAILURE);
					}
					curr_cmd->output_fd = pipe_fd[1];
				}
			}
			else if (curr_cmd->output_fd == -1)
			{
				// SI NO HAY MÁS COMANDOS, USAR `STDOUT_FILENO`
				curr_cmd->output_fd = STDOUT_FILENO;
			}
			curr_cmd->input_fd = input_fd;

			// CREAR PROCESO HIJO PARA EJECUTAR EL COMANDO
			pid = fork();
			if (pid < 0)
			{
				perror("Error creando proceso hijo");
				exit(EXIT_FAILURE);
			}
			// PROCESO HIJO: REDIRIGIR ENTRADA Y SALIDA, Y EJECUTAR COMANDO
			if (pid == 0)
			{
				// TODO: Agregar caso pipe vacia.
				// REDIRECCIÓN DE ENTRADA SI ES NECESAiRIO
				// CASO DE PIPE VACÍA
				if (curr_cmd->input_fd == STDIN_FILENO && curr_cmd->cmd_id > 0)
				{
					int p_empty_fd[2];
					if (pipe(p_empty_fd) == -1)
					{
						perror("Error creando pipe vacío");
						exit(EXIT_FAILURE);
					}
					curr_cmd->input_fd = p_empty_fd[0];
					close(p_empty_fd[1]); // Se cierra el lado de escritura para enviar EOF
				}

				if (curr_cmd->input_fd != STDIN_FILENO)
				{
					if (dup2(curr_cmd->input_fd, STDIN_FILENO) == -1)
					{
						perror("Error redirigiendo entrada");
						exit(EXIT_FAILURE);
					}
					close(curr_cmd->input_fd);
				}

				// REDIRECCIÓN DE SALIDA SI ES NECESARIO
				if (curr_cmd->output_fd != STDOUT_FILENO)
				{
					if (dup2(curr_cmd->output_fd, STDOUT_FILENO) == -1)
					{
						perror("Error redirigiendo salida");
						exit(EXIT_FAILURE);
					}
					close(curr_cmd->output_fd);
				}

				// EJECUTAR EL COMANDO (EXTERNO O BUILTIN)

				execute_external(curr_cmd, envp);
				// exit(EXIT_FAILURE);
			}
			// PROCESO PADRE: CERRAR DESCRIPTORES Y GESTIONAR EL PIPE SIGUIENTE
			else
			{
				if (curr_cmd->output_fd != STDOUT_FILENO)
					close(curr_cmd->output_fd);
				if (curr_cmd->input_fd != STDIN_FILENO)
				{
					close(curr_cmd->input_fd);
					// close(pipe_fd[0]);
					
				}

				// ACTUALIZAR EL INPUT PARA EL SIGUIENTE COMANDO
				if (t_list_exec_cmd->next)
					input_fd = pipe_fd[0];
			}

		}
		t_list_exec_cmd = t_list_exec_cmd->next;
	}

	if (counter_external_commands > 0)
	{
		// CERRAR EL ÚLTIMO INPUT SI NO ES `STDIN_FILENO`
		if (input_fd != STDIN_FILENO)
			close(input_fd);

		// ESPERAR A QUE TODOS LOS PROCESOS HIJOS TERMINEN
		// TODO: Solo se debe ejecutar cuando se ejecutan comandos externos
		int num_children = len_t_list_exec_cmd;
		while (num_children > 0)
		{
			if (wait(NULL) == -1)
				perror("Error esperando proceso hijo");
			else
				num_children--;
		}
	}
	return (TRUE);
}









































/*
 *05/02/2025 16:30
int	execute_commands(t_mini *mini)
{
    t_list	*t_list_exec_cmd;
    t_cmd	*curr_cmd;
    pid_t	pid;
    int		input_fd;
    int		pipe_fd[2];
    int		i;
    int		len_t_list_exec_cmd;
	int		redirection_applied;

    t_list_exec_cmd = mini->exec->first_cmd;
    input_fd = STDIN_FILENO;
    i = 1;
    len_t_list_exec_cmd = ft_lstsize(t_list_exec_cmd);
    while (t_list_exec_cmd)
    {
        curr_cmd = (t_cmd *)t_list_exec_cmd->content;
        curr_cmd->cmd_id = i++;
    	redirection_applied = apply_redirections(curr_cmd);

		if (redirection_applied == TRUE && curr_cmd->input_fd != STDIN_FILENO)
        	curr_cmd->input_fd = input_fd;

		//PIPE
        if (t_list_exec_cmd->next)
        // if (t_list_exec_cmd->next && curr_cmd->output_fd == STDOUT_FILENO)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("Error creando pipe");
                exit(EXIT_FAILURE);
            }
            curr_cmd->output_fd = pipe_fd[1]; // La salida del comando es el pipe
			// curr_cmd->input_fd = pipe_fd[0];
        }
        else
        {
            if (curr_cmd->output_fd == -1)
                curr_cmd->output_fd = STDOUT_FILENO;
        }
        curr_cmd->input_fd = input_fd;
        // curr_cmd->input_fd = pipe_fd[0];

		//HIJO 

        pid = fork();

        if (pid < 0)
        {
            perror("Error creando proceso hijo");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
        	// if (curr_cmd->input_fd == -1 || curr_cmd->input_fd == STDIN_FILENO)
        	if (curr_cmd->input_fd == -1)
        	{
        		int p_empty_fd[2];
        		if (pipe(p_empty_fd) == -1)
        		{
        			perror("Error creando pipe vacío");
        			exit(EXIT_FAILURE);
        		}
        		// Redirigir entrada estándar al pipe vacío
        		dup2(p_empty_fd[0], STDIN_FILENO);
        		close(p_empty_fd[0]);
        		close(p_empty_fd[1]);
        	}

			if (curr_cmd->input_fd != STDIN_FILENO )
			{
				if (dup2(curr_cmd->input_fd, STDIN_FILENO) == -1)
				{
					perror("Error redirigiendo entrada");
					exit(EXIT_FAILURE);
				}
				close(curr_cmd->input_fd);
			}

        	// Redirigir salida si es necesario
        	if (curr_cmd->output_fd != STDOUT_FILENO)
        	{
        		if (dup2(curr_cmd->output_fd, STDOUT_FILENO) == -1)
        		{
        			perror("Error redirigiendo salida");
        			exit(EXIT_FAILURE);
        		}
        		close(curr_cmd->output_fd);
        	}
//EJECUCUION DE COMANDOS
        	char **envp = lst_to_arr(mini->env);
        	if (curr_cmd->is_external == 1)
        		execute_external(curr_cmd, envp);
        	else if (curr_cmd->is_builtin == 1)
        		cases_builtins(mini);

        	exit(EXIT_FAILURE);
        }
    	else // Proceso padre
    	{
    		// Cerrar fds en el padre para evitar bloqueos
    		if (curr_cmd->output_fd != STDOUT_FILENO)
    		{
    			close(curr_cmd->output_fd);
    		}

    		if (curr_cmd->input_fd != STDIN_FILENO)
    		{
    			close(curr_cmd->input_fd);
    		}

    		if (t_list_exec_cmd->next)
    		{
    			input_fd = pipe_fd[0]; // La siguiente entrada será el extremo de lectura del pipe
    		}
		}
		t_list_exec_cmd = t_list_exec_cmd->next;
    }

    if (input_fd != STDIN_FILENO)
        close(input_fd);

    int num_children = len_t_list_exec_cmd;
    while (num_children > 0)
    {
        if (wait(NULL) == -1)
            perror("Error esperando proceso hijo");
        else
            num_children--;
    }

    return (TRUE);
}
*/





//funciona semi bien
/*int	execute_commands(t_mini *mini)
{
    t_list *t_list_exec_cmd = mini->exec->first_cmd;
    t_cmd *curr_cmd;
    pid_t pid;
    int input_fd = STDIN_FILENO;
    int pipe_fd[2];
    int i = 0;
    int len_t_list_exec_cmd = ft_lstsize(t_list_exec_cmd);

    while (t_list_exec_cmd)
    {
        curr_cmd = (t_cmd *)t_list_exec_cmd->content;
        curr_cmd->cmd_id = i++;

    	int redirection_applied = apply_redirections(curr_cmd);
    	// Actualizamos input_fd con la redirección de entrada si se aplicó
    	if (redirection_applied == TRUE && curr_cmd->input_fd != STDIN_FILENO)
    		input_fd = curr_cmd->input_fd;

        if (t_list_exec_cmd->next)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("Error creando pipe");
                exit(EXIT_FAILURE);
            }
            curr_cmd->output_fd = pipe_fd[1];
        }
        else
        {
            if (curr_cmd->output_fd == -1)
                curr_cmd->output_fd = STDOUT_FILENO;
        }
        curr_cmd->input_fd = input_fd;



        pid = fork();

        if (pid < 0)
        {
            perror("Error creando proceso hijo");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
			//esto pasa cuando hay PIPE
			// if (curr_cmd->input_fd != STDIN_FILENO )
			// {
			// 	if (dup2(curr_cmd->input_fd, STDIN_FILENO) == -1)
			// 	{
			// 		perror("Error redirigiendo entrada");
			// 		exit(EXIT_FAILURE);
			// 	}
			// 	close(curr_cmd->input_fd);
			// }

			// if (redirection_applied == FALSE && curr_cmd->output_fd != STDOUT_FILENO)
			// {
			// 	if (dup2(curr_cmd->output_fd, STDOUT_FILENO) == -1)
			// 	{
			// 		perror("Error redirigiendo salida");
			// 		exit(EXIT_FAILURE);
			// 	}
			// 	close(curr_cmd->output_fd);
			// }
        	// Redirigir salida si es necesario
        	if (curr_cmd->output_fd != STDOUT_FILENO)
        	{
        		if (dup2(curr_cmd->output_fd, STDOUT_FILENO) == -1)
        		{
        			perror("Error redirigiendo salida");
        			exit(EXIT_FAILURE);
        		}
        		close(curr_cmd->output_fd);
        	}
//EJECUCUION DE COMANDOS
        	char **envp = lst_to_arr(mini->env);
        	if (curr_cmd->is_external == 1)
        		execute_external(curr_cmd, envp);
        	else if (curr_cmd->is_builtin == 1)
        		cases_builtins(mini);

        	exit(EXIT_FAILURE);
        }
    	else // Proceso padre
  //       {
  //   		if (redirection_applied == TRUE && curr_cmd->output_fd != STDOUT_FILENO)
  //   		{
  //   			close(curr_cmd->output_fd);
  //   		}
  //
  //
  //   	//proceso padrfue
  //
		// 	//cerrar el extremo de escritura en la parte del parte si no es el utlimo comando
		// 	else if (curr_cmd->output_fd != STDOUT_FILENO)
		// 		close(pipe_fd[1]);
		// 	//cerrar el extremo de lectura anterior e el padre si no es stdin
		// 	if (curr_cmd->input_fd != STDIN_FILENO)
		// 		close(curr_cmd->input_fd);
		// 	if (t_list_exec_cmd->next)
		// 		input_fd = pipe_fd[0];
		// }

    	{
    		// Cerrar fds en el padre para evitar bloqueos
    		if (curr_cmd->output_fd != STDOUT_FILENO)
    		{
    			close(curr_cmd->output_fd);
    		}

    		if (curr_cmd->input_fd != STDIN_FILENO)
    		{
    			close(curr_cmd->input_fd);
    		}

    		if (t_list_exec_cmd->next)
    		{
    			input_fd = pipe_fd[0]; // La siguiente entrada será el extremo de lectura del pipe
    		}
    		// else
    		// {
    		// 	close(pipe_fd[0]); // Si es el último comando, cerramos lectura del pipe
    		// }
    	}

		t_list_exec_cmd = t_list_exec_cmd->next;
    }

    if (input_fd != STDIN_FILENO)
        close(input_fd);

    int num_children = len_t_list_exec_cmd;
    while (num_children > 0)
    {
        if (wait(NULL) == -1)
            perror("Error esperando proceso hijo");
        else
            num_children--;
    }

    return (TRUE);
}

*/





/*int execute_commands(t_mini *mini)
{
    t_list *t_list_exec_cmd = mini->exec->first_cmd;
    t_cmd *curr_cmd;
    pid_t pid;
    int input_fd = STDIN_FILENO;
    int pipe_fd[2];
    int i = 0;
    int len_t_list_exec_cmd = ft_lstsize(t_list_exec_cmd);

    while (t_list_exec_cmd)
    {
        curr_cmd = (t_cmd *)t_list_exec_cmd->content;
        curr_cmd->cmd_id = i++;

        // Aplicar redirecciones antes del fork
        int redirection_applied = apply_redirections(curr_cmd);

        // Si hay redirección de entrada, actualizar input_fd
        if (redirection_applied == TRUE && curr_cmd->input_fd != STDIN_FILENO)
        {
            input_fd = curr_cmd->input_fd;
        }

        // Configuración de pipes si hay más comandos después
        if (t_list_exec_cmd->next)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("Error creando pipe");
                exit(EXIT_FAILURE);
            }
            curr_cmd->output_fd = pipe_fd[1]; // La salida del comando será el pipe
        }
        else
        {
            if (curr_cmd->output_fd == -1)
                curr_cmd->output_fd = STDOUT_FILENO; // Último comando usa la salida estándar
        }

        curr_cmd->input_fd = input_fd;

        // Crear proceso hijo
        pid = fork();

        if (pid < 0)
        {
            perror("Error creando proceso hijo");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) // Proceso hijo
        {
            // Redirigir salida si es necesario
            if (curr_cmd->output_fd != STDOUT_FILENO)
            {
                if (dup2(curr_cmd->output_fd, STDOUT_FILENO) == -1)
                {
                    perror("Error redirigiendo salida");
                    exit(EXIT_FAILURE);
                }
                close(curr_cmd->output_fd);
            }

            // Ejecutar el comando correspondiente
            char **envp = lst_to_arr(mini->env);
            if (curr_cmd->is_external == 1)
                execute_external(curr_cmd, envp);
            else if (curr_cmd->is_builtin == 1)
                cases_builtins(mini);

            exit(EXIT_FAILURE);
        }
        else // Proceso padre
        {
            // Cerrar file descriptors en el padre para evitar bloqueos
            if (curr_cmd->output_fd != STDOUT_FILENO)
            {
                close(curr_cmd->output_fd);
            }

            if (curr_cmd->input_fd != STDIN_FILENO)
            {
                close(curr_cmd->input_fd);
            }

            // Si hay un siguiente comando, el input_fd del siguiente será el extremo de lectura del pipe
            if (t_list_exec_cmd->next)
            {
                input_fd = pipe_fd[0];
            }
        }

        t_list_exec_cmd = t_list_exec_cmd->next;
    }

    // Cerrar último input_fd si no es STDIN
    if (input_fd != STDIN_FILENO)
        close(input_fd);

    // Esperar a que todos los procesos hijos terminen
    int num_children = len_t_list_exec_cmd;
    while (num_children > 0)
    {
        if (wait(NULL) == -1)
            perror("Error esperando proceso hijo");
        else
            num_children--;
    }

    return (TRUE);
}*/
