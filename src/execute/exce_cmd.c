
#include "../../includes/minishell.h"


static void	execute_external(t_cmd *cmd, char **envp)
{
	if (cmd->input_fd != -1)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
		{
			perror("Error duplicando input_fd para comando externo");
			exit(EXIT_FAILURE);
		}
		close(cmd->input_fd);
	}

	if (cmd->output_fd != -1)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
		{
			perror("Error duplicando output_fd para comando externo");
			exit(EXIT_FAILURE);
		}
		close(cmd->output_fd);
	}
	execve(cmd->cmd_path, cmd->cmd_args, envp);
	perror("Error ejecutando comando externo");
	exit(EXIT_FAILURE);
}



void	handle_commands(t_mini *mini)
{
	t_list	*current;
	t_cmd	*cmd;

	current = mini->exec->first_cmd;
	while (current)
	{
		cmd = (t_cmd *)current->content;

		if (cmd->is_builtin)
		{
			//execute_builtin(cmd);
			printf("Comando builtin: %s\n", cmd->cmd);
		}
		else if (cmd->is_external)
		{
			pid_t pid = fork();
			if (pid < 0)
			{
				perror("Error creando proceso hijo");
				exit(EXIT_FAILURE);
			}
			if (pid == 0) // Proceso hijo
			{
				execute_external(cmd, lst_to_arr(mini->env));
			}
			wait(NULL); // Esperar al hijo
		}

		current = current->next;
	}
}