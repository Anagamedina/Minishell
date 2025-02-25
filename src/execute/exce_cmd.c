/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:02:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/25 15:00:03 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_child(t_cmd *curr_cmd, t_mini *mini)
{
	heredoc(curr_cmd);
	if (apply_redirections(curr_cmd) > 0)
	{
		if (curr_cmd->input_fd != STDIN_FILENO)
			redirect_in(curr_cmd->input_fd);
		if (curr_cmd->output_fd != STDOUT_FILENO)
			redirect_out(curr_cmd->output_fd);
	}
	else
	{
		if (curr_cmd->output_fd != STDOUT_FILENO)
			redirect_out (curr_cmd->output_fd);
		if (curr_cmd->input_fd != STDIN_FILENO)
			redirect_in(curr_cmd->input_fd);
	}
	execute_builtin_or_external(curr_cmd, mini);
}

void	handle_parent(t_cmd *curr_cmd, int *pipe_fd, int *input_fd)
{
	if (curr_cmd->input_fd != STDIN_FILENO)
		close(curr_cmd->input_fd);
	if (curr_cmd->output_fd != STDOUT_FILENO)
		close(curr_cmd->output_fd);
	if (!curr_cmd->last_cmd)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	else
		close(pipe_fd[0]);
}


int handle_redirection_without_command(t_cmd *cmd)
{
	t_list *redir_node;
	t_redir *curr_redir;

	if (!cmd->redir_list)
		return (FALSE);

	printf("DEBUG: No hay comando, pero hay redirecciones. Creando archivos vacíos...\n");

	redir_node = cmd->redir_list;
	while (redir_node)
	{
		curr_redir = (t_redir *)redir_node->content;
		if (curr_redir->type == REDIR_OUT || curr_redir->type == REDIR_APPEND)
		{
			int fd = open_file(curr_redir->filename, curr_redir->type);
			if (fd == -1)
				perror("Error creando archivo vacío");
			else
				close(fd);
		}
		redir_node = redir_node->next;
	}
	return (TRUE);
}



int pre_executor(t_mini *mini, t_cmd *cmd)
{
	int saved_stdout = -1;

	// Si el comando no tiene argumentos y solo hay redirección, manejarlo sin ejecutar un comando
	if (!cmd->cmd_args || !cmd->cmd_args[0])
	{
		if (handle_redirection_without_command(cmd) == TRUE)
			return (TRUE);
		return (FALSE);
	}

	// Si el comando está en un pipeline, NO ejecutarlo en el padre
	if (cmd->has_pipe == TRUE)
		return (FALSE);

	// Si NO es un builtin, continuar con el flujo normal
	if (!is_builtin_command(cmd->cmd))
		return (FALSE);

	// Si es un builtin y NO tiene redirección, ejecutarlo directamente
	if (!cmd->redir_list)
	{
		cases_builtins(mini, cmd);
		return (TRUE);
	}

	// Si es un builtin y TIENE redirección, manejarlo en el padre
	if (apply_redirections(cmd) == -1)
		return (FALSE);

	// Guardar stdout si hay redirección de salida
	if (cmd->output_fd != STDOUT_FILENO)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (saved_stdout == -1)
			return (perror("Error guardando stdout"), FALSE);
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
			return (perror("Error redirigiendo salida"), FALSE);
		close(cmd->output_fd);
	}

	// Ejecutar el builtin en el padre
	cases_builtins(mini, cmd);

	// Restaurar stdout original si fue cambiado
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}

	return (TRUE);
}


int	execute_commands(t_mini *mini)
{
	t_list	*t_list_exec_cmd;
	t_cmd	*curr_cmd;
	int		input_fd;
	int		pipe_fd[2];
	int		i;

	i = 0;
	input_fd = STDIN_FILENO;
	t_list_exec_cmd = mini->exec->first_cmd;
	while (t_list_exec_cmd)
	{
		curr_cmd = (t_cmd *)t_list_exec_cmd->content;
		curr_cmd->cmd_id = i++;

		if (curr_cmd->is_builtin == 1 && !curr_cmd->has_pipe)
		{
			// setup_fds(curr_cmd, pipe_fd, &input_fd);
			if (pre_executor(mini, curr_cmd) == TRUE)
			{
	           t_list_exec_cmd = t_list_exec_cmd->next;
               continue;
			}
		}
		setup_fds(curr_cmd, pipe_fd, &input_fd);
		fork_and_execute(curr_cmd, mini, pipe_fd, &input_fd);
		t_list_exec_cmd = t_list_exec_cmd->next;
	}
	wait_children(mini);
	return (TRUE);
}