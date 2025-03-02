/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:48:05 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/01 19:32:26 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	*replace_variable(char *expanded_line, \
		char *var_name, char *var_value, int i)
{
	char	*prefix;
	char	*new_line;

	prefix = ft_substr(expanded_line, 0, i);
	new_line = ft_strjoin(prefix, var_value);
	free(prefix);
	prefix = ft_strjoin(new_line, &expanded_line[i + ft_strlen(var_name) + 1]);
	free(new_line);
	return (prefix);
}

char	*expand_variables(char *line)
{
	char	*expanded_line;
	char	*var_name;
	char	*var_value;
	char	*new_line;
	int		i;

	i = 0;
	expanded_line = ft_strdup(line);
	while (expanded_line[i])
	{
		if (expanded_line[i] == '$' && (ft_isalnum(expanded_line[i + 1]) || \
					expanded_line[i + 1] == '_'))
		{
			var_name = extract_var_name(&expanded_line[i + 1]);
			var_value = getenv(var_name);
			if (var_value)
			{
				new_line = replace_variable(expanded_line, \
						var_name, var_value, i);
				free(expanded_line);
				expanded_line = new_line;
			}
			free(var_name);
		}
		i++;
	}
	return (expanded_line);
}


char	*generate_heredoc_filename(int nbr_heredoc)
{
	char	*num_str;
	char	*tmp_name;

	num_str = ft_itoa(nbr_heredoc);
	if (!num_str)
		return (NULL);
	tmp_name = ft_strjoin("/tmp/heredoc", num_str);
	free(num_str);
	if (!tmp_name)
		return (NULL);
	return (tmp_name);
}




int	write_heredoc_content(int fd_tmp, char *delimiter, int expand_vars)
{
	char	*line;
	char	*expand_line;

	line = readline("> ");
	while (line && ft_strcmp(line, delimiter) != 0)
	{
		if (expand_vars)
		{
			expand_line = expand_variables(line);
		}
		else
			expand_line = ft_strdup(line);
		if (expand_line)
		{
			write(fd_tmp, expand_line, ft_strlen(expand_line));
			write(fd_tmp, "\n", 1);
			free(expand_line);
		}
		free(line);
		line = readline("> ");
	}
	free(line);
	return (0);
}



int	create_heredoc(t_redir *redir, int nbr_heredoc, int expand_vars)
{
	int		fd_tmp;
	char	*tmp_name;
	// pid_t	pid;
	// int		status;

	tmp_name = generate_heredoc_filename(nbr_heredoc);
	if (!tmp_name)
		return (-1);
	fd_tmp = open_file(tmp_name, HEREDOC);
	if (fd_tmp == -1)
	{
		free(tmp_name);
		return (-1);
	}
	// setup_signals(HERE_DOC);
    write_heredoc_content(fd_tmp, redir->filename, expand_vars);
    close(fd_tmp);
	close(fd_tmp);
	free(redir->filename);
	redir->filename = ft_strdup(tmp_name);
	free(tmp_name);
	return (0);
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
