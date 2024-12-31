/*void	do_execve(t_tokens *tokens, t_cmd *cmd)
{
	char	*path;
	char	**lst_env;
	int		i;

	i = 0;
	lst_env = lst_to_arr((t_token **) NULL, tokens->env);
	do_signals(NON_STANDAR);
	blt_and_free(tokens, cmd);
	execve(cmd->args[0], cmd->args, lst_env);
	if (tokens->paths)
	{
		while (tokens->paths[i])
		{
			path = ft_strjoin(ft_strjoin(tokens->paths[i], "/", NONE),
							  cmd->args[0], FIRST);
			execve(path, cmd->args, lst_env);
			free(path);
			i ++;
		}
	}
	free_lst(lst_env);
	cmd->exit_code = 127;
	exit_error(cmd->args[0], "command not found\n", tokens, cmd);
}*/