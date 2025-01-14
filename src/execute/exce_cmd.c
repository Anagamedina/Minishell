
#include "../../includes/minishell.h"





//una funcion que ejecute builtins tomando como argumento char **cmd_list y y un char *tmp_cmd



//funcion para  crear una funcion que cree una pipe, y adjudicando el ultimo pipe como el utlimo, y que segun el indice de la pipe haga una cosa u otra es decir si son pipes intermedias o la utlima



//funcion para Redigir la entrada y salida de los comandos externos y builtins



//una funcion que ejecute comandos externos tomando como argumento t_cmd *cmd , t_pipe *pipes , int id_cmd


void	execute_external(t_cmd *cmd, char **envp)
{
	if (cmd->input_fd != -1)
	{
		if (dup2(cmd->input_fd, STDIN_FILENO) == -1)
		{
			perror("Error redirigiendo entrada");
			exit(EXIT_FAILURE);
		}
		close(cmd->input_fd);
	}
	if (cmd->output_fd != -1)
	{
		if (dup2(cmd->output_fd, STDOUT_FILENO) == -1)
		{
			perror("Error redirigiendo salida");
			exit(EXIT_FAILURE);
		}
		close(cmd->output_fd);
	}
	if (cmd->is_external)
	{
		execve(cmd->cmd_path, cmd->cmd_args, envp);
		perror("Error ejecutando comando externo");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Comando builtin: %s\n", cmd->cmd);
		exit(EXIT_SUCCESS);
	}
}

void	handle_commands(t_mini *mini)
{
	t_list	*current;
	t_cmd	*cmd;
	pid_t	pid;
	int 	pipe_fd[2];
	int 	input_fd = -1;

	current = mini->exec->first_cmd;
	while (current)
	{
		cmd = (t_cmd *)current->content;
		if (current->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("Error creando pipe");
				exit(EXIT_FAILURE);
			}
			cmd->output_fd = pipe_fd[1];
		}
		else
		{
			cmd->output_fd = -1;
		}

		cmd->input_fd = input_fd;
		pid = fork();
		if (pid < 0)
		{
			perror("Error creando proceso hijo");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			execute_external(cmd, lst_to_arr(mini->env));
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (cmd->input_fd!= -1)
				close(cmd->input_fd);
			if (cmd->output_fd != -1)
				close(cmd->output_fd);
			input_fd = pipe_fd[0];
			waitpid(pid, NULL, 0);
		}

		current = current->next;
	}
}


//******************COPIA**************************/

/*void	execute_external(t_cmd *cmd, int input_fd, int pipe_fd[2], char **envp)
{
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("Error redirigiendo entrada");
			exit(EXIT_FAILURE);
		}
		close(input_fd);
	}

	if (pipe_fd)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("Error redirigiendo salida");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}

	if (cmd->is_external)
	{
		execve(cmd->cmd_path, cmd->cmd_args, envp);
		perror("Error ejecutando comando externo");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Comando builtin: %s\n", cmd->cmd);
		exit(EXIT_SUCCESS);
	}
}

void	handle_commands(t_mini *mini)
{
	t_list	*current;
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_pipe_fd = -1; // Descriptor de lectura del pipe anterior
	pid_t	pid;

	current = mini->exec->first_cmd;
	while (current)
	{
		cmd = (t_cmd *)current->content;

		if (current->next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("Error creando pipe");
				exit(EXIT_FAILURE);
			}
		}

		pid = fork();
		if (pid < 0)
		{
			perror("Error creando proceso hijo");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			execute_external(cmd, prev_pipe_fd, pipe_fd, lst_to_arr(mini->env));
		}
		else
		{
			if (prev_pipe_fd != -1)
				close(prev_pipe_fd);
			if (current->next)
				close(pipe_fd[1]);
			prev_pipe_fd = pipe_fd[0];
			waitpid(pid, NULL, 0);
		}

		current = current->next;
	}
}
*/


/*static void	execute_external(t_cmd *cmd, char **envp)
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
*/

/*
void	handle_commands(t_mini *mini)
{
	t_list	*current;
	t_cmd	*cmd;
	int		pipe_fd[2];
	int		prev_pipe_fd = -1;
	//int		pre_pipe_end[2] = {-1, -1};

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
			pipe(pipe_fd);
			cmd->pipe[0] = pipe_fd[0];
			cmd->pipe[1] = pipe_fd[1];
			pid_t pid = fork();
			if (pid < 0)
			{
				perror("Error creando proceso hijo");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				execute_external(cmd, lst_to_arr(mini->env));
			}
			else
			{
				wait(NULL);
				if (prev_pipe_fd[0] != -1)
					close(prev_pipe_fd[0]);
				close(pipe_fd[1]);
				prev_pipe_fd[0] = pipe_fd[0];
			}
		}

		current = current->next;
	}
}*/