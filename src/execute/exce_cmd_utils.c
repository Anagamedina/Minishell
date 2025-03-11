/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:11:54 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/11 05:10:47 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
void	execute_external(t_cmd *cmd, char **envp)
{
	execve(cmd->cmd_path, cmd->cmd_args, envp);
	perror("Error ejecutando comando externo con execve");
	exit(EXIT_FAILURE);
}
*/

void	execute_external(t_cmd *curr_cmd, char **envp)
{
	restore_signal_to_default(SIGINT);
	restore_signal_to_default(SIGQUIT);
	if (execve(curr_cmd->cmd_path, curr_cmd->cmd_args, envp) == -1)
	{
		perror("Error ejecutando comando externo con execve");
		exit(127);
	}
}


void	redirect_in(int input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(input_fd);
}

void	redirect_out(int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(output_fd);
}

void	execute_builtin_or_external(t_cmd *curr_cmd, t_mini *mini)
{
	int	tmp_exit_status;

	// Si el comando es un builtin, ejecutarlo directamente
	if (curr_cmd->is_builtin == 1)
	{
		tmp_exit_status = cases_builtins(mini, curr_cmd);
		mini->exit_status = tmp_exit_status;
		exit(tmp_exit_status);
	}

	// Si es un comando externo, validarlo antes de ejecutar
	else if (curr_cmd->is_external == 1)
	{
		// Si no tiene un path válido, el comando no existe
		if (!curr_cmd->cmd_path)
			exit(127);  // Código de error "command not found"

		// Si no hay variables de entorno disponibles, fallo crítico
		if (!mini->envp_to_array)
			exit(EXIT_FAILURE);

		// Restaurar señales antes de ejecutar un nuevo proceso
		restore_signal_to_default(SIGINT);
		restore_signal_to_default(SIGQUIT);

		// Ejecutar el comando externo con execve()
		execute_external(curr_cmd, mini->envp_to_array);
	}

	// Si por alguna razón no se ejecutó nada, salir con error
	exit(EXIT_FAILURE);
}


/*
void	execute_builtin_or_external(t_cmd *curr_cmd, t_mini *mini)
{
	int	tmp_exit_status;

	if (curr_cmd->is_builtin == 1)
	{
		tmp_exit_status = cases_builtins(mini, curr_cmd);
		mini->exit_status = tmp_exit_status;
		exit(tmp_exit_status);
	}
	else if (curr_cmd->is_external == 1)
	{
		if (!curr_cmd->cmd_path)
		{
			exit(127);
		}
		if (!mini->envp_to_array)
			exit(EXIT_FAILURE);
		execute_external(curr_cmd, mini->envp_to_array);
	}
	exit(EXIT_FAILURE);
}
*/
