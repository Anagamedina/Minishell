/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:11:54 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/05 22:29:46 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_external(t_cmd *cmd, char **envp)
{
	// if (!cmd || !envp)  // ✅ Verifica que `cmd` y `envp` existen antes de ejecutar
	// 	exit(EXIT_FAILURE);

	execve(cmd->cmd_path, cmd->cmd_args, envp);

	// Si `execve` falla, muestra el error y finaliza
	perror("Error ejecutando comando externo con execve");
	exit(EXIT_FAILURE);
}

/*void	execute_external(t_cmd *cmd, char **envp)
{
	execve(cmd->cmd_path, cmd->cmd_args, envp);
	perror("Error ejecutando comando externo con execve");
	exit(EXIT_FAILURE);
}
*/

void	redirect_in(int input_fd)
{
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		//perror("Error redirigiendo entrada");
		exit(EXIT_FAILURE);
	}
	close(input_fd);
}

void	redirect_out(int output_fd)
{
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
	//	perror("Error redirigiendo salida a archivo");
		exit(EXIT_FAILURE);
	}
	close(output_fd);
}

/*void	execute_builtin_or_external(t_cmd *curr_cmd, t_mini *mini)
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
		if (curr_cmd->cmd_path == NULL)
		{
			return ;
		}
		execute_external(curr_cmd, mini->envp_to_array);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}*/

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
			exit(127);  // ✅ Salida estándar de bash cuando no encuentra comando

		if (!mini->envp_to_array)  // ✅ Evita acceso a memoria inválida
			exit(EXIT_FAILURE);

		// if (!curr_cmd->cmd || !mini->envp_to_array)  // ✅ Verifica que `cmd` y `envp` existen antes de ejecutar
		// 	exit(EXIT_FAILURE);
		execute_external(curr_cmd, mini->envp_to_array);
	}
	exit(EXIT_FAILURE);
}
