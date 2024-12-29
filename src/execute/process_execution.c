/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 13:28:28 by anamedin          #+#    #+#             */
/*   Updated: 2024/10/14 00:25:10 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void child_1(t_pipex *pipex, t_cmd *cmd, int *pipe_fd)
{
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);
    close(pipe_fd[0]);

    dup2(pipex->input_fd, STDIN_FILENO);
    close(pipex->input_fd);
	execve(cmd->cmd_args[0], cmd->cmd_args, pipex->env);
    perror("execve failed");
    exit(EXIT_FAILURE);
}

static void child_2(t_pipex *pipex, t_cmd *cmd, int *pipe_fd)
{
    dup2(pipe_fd[0], STDIN_FILENO); 
    close(pipe_fd[1]); 
    close(pipe_fd[0]); 

    dup2(pipex->output_fd, STDOUT_FILENO);
    close(pipex->output_fd);
    execve(cmd->next->cmd_args[0], cmd->next->cmd_args, pipex->env);
    perror("execve failed");
    exit(EXIT_FAILURE);

}



void execute_child(t_pipex *pipex, t_cmd *cmd, int *pipe_fd)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Error: Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
        child_1(pipex, cmd, pipe_fd);
    close(pipe_fd[1]); // importamte!
    pid_t pid2 = fork();
    if (pid2 < 0)
    {
        perror("Error: Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0)
        child_2(pipex, cmd, pipe_fd);

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    wait(NULL);
    wait(NULL);
}

/******* Manejar la ejecución de los comandos ************/
void    handle_commands(t_pipex *pipex)
{
    t_cmd *cmd;
    int pipe_fd[2];

    cmd = pipex->first_cmd;
    while (cmd && cmd->next)
    {
        if (pipe(pipe_fd) == -1)
        {
            perror("Error: Pipe creation failed");
            exit(EXIT_FAILURE);
        }
        execute_child(pipex, cmd, pipe_fd);
        write(2, "entro\n", 6);
        cmd = cmd->next;

        // close(pipex->input_fd);
        // close(pipex->output_fd);
    }
}
