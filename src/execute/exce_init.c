
#include "../../includes/minishell.h"

static int	open_files(t_mini *mini, char **argv, int argc)
{
	mini->exec->pipe_input_fd = open(argv[1], O_RDONLY);
	if (mini->exec->pipe_input_fd == -1)
	{
		perror("Error: Cannot open INPUT file");
		return (0);
	}
	mini->exec->pipe_output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (mini->exec->pipe_output_fd == -1)
	{
		perror("Error: Cannot open OUTPUT file");
		close(mini->exec->pipe_input_fd);
		return (0);
	}
	return (1);
}
t_exec	*init_exec(char **envp)
{
	t_exec	*exec_info;

	exec_info = malloc(sizeof(t_exec));
	if (!exec_info)
		return NULL;
	//exec_info->first_cmd = (t_list *) init_command();
	exec_info->first_cmd = NULL;
	exec_info->env_vars = lst_to_arr(NULL, envp);
	exec_info->pipe_input_fd = -1;
	exec_info->pipe_output_fd = -1;
	exec_info->cmd_count = 0;
	exec_info->paths = get_path(envp);

	return exec_info;
}