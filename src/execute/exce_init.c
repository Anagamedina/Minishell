
#include "../../includes/minishell.h"


t_exec	*init_exec(	char **envp)
{
	t_exec	*exec_info;

	exec_info = malloc(sizeof(t_exec));
	if (!exec_info)
		return NULL;
	//exec_info->first_cmd = (t_list *) init_command();
	exec_info->first_cmd = NULL;
	exec_info->env_vars = lst_to_arr(NULL);
	exec_info->pipe_input_fd = -1;
	exec_info->pipe_output_fd = -1;
	exec_info->cmd_count = 0;
	exec_info->paths = get_path(envp);

	return exec_info;
}