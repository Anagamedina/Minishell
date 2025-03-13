/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:48:05 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/11 23:56:48 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//TODO: setup_signals(remove NULL)
int	write_heredoc_content(int fd_tmp, char *delimiter, int expand_vars)
{
	char	*line;
	char	*expand_line;

	setup_signals(HERE_DOC, NULL);
	line = readline("> ");
	while (line && ft_strcmp(line, delimiter) != 0)
	{
		if (expand_vars)
			expand_line = expand_variables(line);
		else
			expand_line = ft_strdup(line);
		if (expand_line)
		{
			ft_putendl_fd(expand_line, fd_tmp);
			free(expand_line);
		}
		free(line);
		line = readline("> ");
	}
	return (free(line), 0);
}

int	create_heredoc(t_redir *redir, int nbr_heredoc, int expand_vars)
{
	int		fd_tmp;
	char	*tmp_name;

	tmp_name = generate_heredoc_filename(nbr_heredoc);
	if (!tmp_name)
		return (-1);
	fd_tmp = open_file(tmp_name, HEREDOC);
	if (fd_tmp == -1)
	{
		free(tmp_name);
		return (-1);
	}
	write_heredoc_content(fd_tmp, redir->filename, expand_vars);
	close(fd_tmp);
	free(redir->filename);
	redir->filename = ft_strdup(tmp_name);
	free(tmp_name);
	return (0);
}

void	child_heredoc(t_tokens *curr_token, t_mini *mini)
{
	pid_t	pid;
	t_redir	*redir;
	int		status;

	redir = (t_redir *)curr_token;
	pid = fork();
	if (pid < 0)
	{
		free_mini(mini);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		setup_signals(HERE_DOC, mini);
		if (create_heredoc(redir, 0, 1) == -1)
			exit(1);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return ;
	}
}

int	heredoc(t_cmd *cmd)
{
	t_list		*redir_node;
	t_redir		*curr_redir;
	int			nbr_heredoc;
	int			expand_vars;

	expand_vars = 0;
	redir_node = cmd->redir_list;
	nbr_heredoc = 0;
	while (redir_node)
	{
		curr_redir = (t_redir *)redir_node->content;
		if (curr_redir->type == HEREDOC)
		{
			expand_vars = !(curr_redir->filename[0] == '"' || \
				curr_redir->filename[0] == '\'');
			if (create_heredoc(curr_redir, nbr_heredoc, expand_vars) == -1)
			{
				perror("Error creando heredoc");
				return (-1);
			}
			nbr_heredoc++;
		}
		redir_node = redir_node->next;
	}
	return (0);
}
