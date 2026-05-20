/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 13:30:00 by catalinab         #+#    #+#             */
/*   Updated: 2026/05/20 13:30:00 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Ejecuta un nodo de tipo comando.
 * Aquí es donde se aplican las expansiones de variables antes de la ejecución final.
 */
static int	execute_command_node(t_ast_node *node, t_mini *mini)
{
	t_cmd	*cmd_struct;
	int		status;

	if (!node->args || !node->args[0])
		return (0);
	
	/* 1. Crear estructura t_cmd compatible con el ejecutor actual */
	/* Nota: Esto es una simplificación para integrar con tu código existente */
	cmd_struct = init_command();
	if (!cmd_struct)
		return (1);
	
	cmd_struct->cmd = ft_strdup(node->args[0]);
	cmd_struct->cmd_args = node->args; // Usamos los del nodo (ojo con la liberación)
	
	/* 2. Determinar si es builtin o externo */
	if (is_builtin_command(cmd_struct->cmd))
		status = cases_builtins(mini, cmd_struct);
	else
		execute_external(cmd_struct, mini->envp_to_array);
	
	/* Limpiar solo lo necesario (no los args que pertenecen al nodo) */
	free(cmd_struct->cmd);
	free(cmd_struct);
	return (status);
}

/**
 * Ejecuta un nodo de tipo pipe.
 * Crea un pipe, hace fork y ejecuta recursivamente las ramas.
 */
static int	execute_pipe_node(t_ast_node *node, t_mini *mini)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	
	pid_left = fork();
	if (pid_left == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(execute_ast(node->left, mini));
	}
	
	pid_right = fork();
	if (pid_right == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exit(execute_ast(node->right, mini));
	}
	
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	return (WEXITSTATUS(status));
}

/**
 * Ejecuta un nodo de tipo redirección.
 * Abre el archivo, redirige el FD correspondiente y ejecuta el hijo izquierdo.
 */
static int	execute_redir_node(t_ast_node *node, t_mini *mini)
{
	int	fd;
	int	old_fd;
	int	status;

	if (node->redir_type == REDIR_OUT)
		fd = open(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->redir_type == REDIR_APPEND)
		fd = open(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->redir_type == REDIR_IN)
		fd = open(node->file, O_RDONLY);
	else
		return (1);

	if (fd == -1)
		return (perror(node->file), 1);

	/* Guardar FD original para restaurar después (opcional si es en un subproceso) */
	if (node->redir_type == REDIR_IN)
		old_fd = dup(STDIN_FILENO);
	else
		old_fd = dup(STDOUT_FILENO);

	if (node->redir_type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);

	status = execute_ast(node->left, mini);

	/* Restaurar FD original */
	if (node->redir_type == REDIR_IN)
		dup2(old_fd, STDIN_FILENO);
	else
		dup2(old_fd, STDOUT_FILENO);
	close(old_fd);

	return (status);
}

/**
 * Función principal de ejecución del AST.
 * Recorre el árbol recursivamente y ejecuta cada nodo según su tipo.
 */
int	execute_ast(t_ast_node *node, t_mini *mini)
{
	if (!node)
		return (0);
	
	if (node->type == NODE_PIPE)
		return (execute_pipe_node(node, mini));
	else if (node->type == NODE_REDIRECT)
		return (execute_redir_node(node, mini));
	else if (node->type == NODE_COMMAND)
		return (execute_command_node(node, mini));
	
	return (1);
}
