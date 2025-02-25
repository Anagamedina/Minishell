/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excec_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:05:02 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/24 21:47:24 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void	setup_fds(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
	if (!curr_cmd->last_cmd)
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
		curr_cmd->output_fd = STDOUT_FILENO;
	}
	curr_cmd->input_fd = *input_fd;
}*/

void	setup_fds(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
	// Si NO hay redirección de salida, usa un pipe si no es el último comando
	if (!curr_cmd->last_cmd && curr_cmd->output_fd == STDOUT_FILENO)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Error creando pipe");
			exit(EXIT_FAILURE);
		}
		curr_cmd->output_fd = pipe_fd[1];  // Usa el pipe para salida solo si no hay redirección
	}

	// No sobrescribir si ya hay redirección de entrada
	if (*input_fd >= 0)
		curr_cmd->input_fd = *input_fd;
	else
		curr_cmd->input_fd = STDIN_FILENO;  // Default si input_fd es inválido
}


void	wait_children(t_mini *mini)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
}

void	fork_and_execute(t_cmd *cmd, t_mini *mini, int pipe_fd[2], int *input_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Error creando proceso hijo");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		handle_child(cmd, mini);
		exit(EXIT_SUCCESS);
	}
	else
		handle_parent(cmd, pipe_fd, input_fd);
}