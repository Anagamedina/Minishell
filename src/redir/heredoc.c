/*
 *
void redirect_file(int fd, int target_fd)
{
    if (dup2(fd, target_fd) == -1)
    {
        perror("Error duplicando descriptor");
        close(fd);
        exit(EXIT_FAILURE);
    }
    close(fd);
}




 int handle_empty_input(t_cmd *cmd)
{
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1)
    {
        perror("Error creando pipe vacío");
        exit(EXIT_FAILURE);
    }

    redirect_file(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
    return (0);
}

void process_redirections(t_cmd *cmd)
{
    t_list *current = cmd->redir_list;

    while (current)
    {
        t_redir *redir = (t_redir *)current->content;
        int fd = open_file(redir->filename, redir->type);

        // Si la redirección es de entrada y el archivo no existe, usa un flujo vacío
        if (fd == -1 && redir->type == REDIR_IN)
        {
            fprintf(stderr, "Advertencia: Archivo '%s' no encontrado. Usando entrada vacía.\n", redir->filename);
            handle_empty_input(cmd);
            current = current->next;
            continue;
        }

        // Manejar redirecciones normales
        if (redir->type == REDIR_IN)
        {
            if (cmd->input_fd != -1)
                close(cmd->input_fd);
            cmd->input_fd = fd;
        }
        else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
        {
            if (cmd->output_fd != -1)
                close(cmd->output_fd);
            cmd->output_fd = fd;
        }

        current = current->next;
    }

    // Aplicar las redirecciones configuradas a stdin y stdout
    if (cmd->input_fd != -1)
        redirect_file(cmd->input_fd, STDIN_FILENO);
    if (cmd->output_fd != -1)
        redirect_file(cmd->output_fd, STDOUT_FILENO);
}

 void execute_command(t_cmd *cmd)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // Proceso hijo
        process_redirections(cmd); // Configurar redirecciones
        execve(cmd->cmd, cmd->cmd_args, NULL);
        perror("Error ejecutando el comando");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("Error al crear proceso");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Proceso padre
        wait(NULL); // Esperar al hijo
    }
}
 */
