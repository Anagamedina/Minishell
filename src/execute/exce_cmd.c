
#include "../../includes/minishell.h"




/*static void	execute_child(t_mini *mini, t_cmd *cmd, int *pipe_fd)
{
	if (fork() == 0)
	{
		if (cmd->input_fd != -1)
			dup2(cmd->input_fd, STDIN_FILENO);
		if (cmd->output_fd != -1)
			dup2(cmd->output_fd, STDOUT_FILENO);
		else if (cmd->next)
			dup2(pipe_fd[1], STDOUT_FILENO);

		close(pipe_fd[0]);
		execve(cmd->cmd, cmd->cmd_flags, mini->exec->env_vars);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	close(pipe_fd[1]);
}





void	execute_commands(t_mini *mini)
{
	t_cmd	*cmd = (t_cmd *)mini->exec->first_cmd;
	int		pipe_fd[2];

	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("Error al crear pipe");
			return;
		}

		execute_child(mini, cmd, pipe_fd);
		cmd = cmd->next;
	}
}*/



















static void	child_1(t_mini *mini, t_cmd *cmd, int *pipe_fd)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	dup2(mini->exec->pipe_input_fd, STDIN_FILENO);
	close(mini->exec->pipe_input_fd);
	execve(cmd->cmd_args[0], cmd->cmd_args, mini->exec->env_vars);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

static void	child_2(t_mini *mini, t_cmd *cmd, int *pipe_fd)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	dup2(mini->exec->pipe_output_fd, STDOUT_FILENO);
	close(mini->exec->pipe_output_fd);
	execve(cmd->next->cmd_args[0], cmd->next->cmd_args, mini->exec->env_vars);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

void	execute_child(t_mini *mini, t_cmd *cmd, int *pipe_fd)
{
	pid_t	pid;
	pid_t	pid2;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_1(mini, cmd, pipe_fd);
	close(pipe_fd[1]);
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("Error: Fork failed");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
		child_2(mini, cmd, pipe_fd);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
	wait(NULL);
}

void	handle_commands(t_mini *mini)
{
	t_cmd	*cmd;
	int		pipe_fd[2];

	cmd = (t_cmd *)mini->exec->first_cmd;
	while (cmd && cmd->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Error: Pipe creation failed");
			exit(EXIT_FAILURE);
		}
		execute_child(mini, cmd, pipe_fd);
		cmd = cmd->next;
		close(mini->exec->pipe_input_fd);
		close(mini->exec->pipe_output_fd);
	}
}
