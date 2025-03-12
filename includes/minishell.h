/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:59:09 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/12 00:25:44 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "prototype.h"
# include "free_structs.h"
# include "macros.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/termios.h>
# include <signal.h>

typedef enum e_type_token
{
	WORD = 0,
	REDIR_IN,
	REDIR_APPEND,
	REDIR_OUT,
	BUILTINS,
	CMD_EXTERNAL,
	DELIMITER,
	NULL_TYPE,
	PIPE,
	HEREDOC,
	FILENAME,
}	t_type_token;

typedef struct s_tokens
{
	char			*str;
	t_type_token	type_token;
	size_t			length;
	int				is_valid_cmd;
	int				id_token;
	struct s_tokens	*next;
	struct s_tokens	*prev;
}	t_tokens;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_split_data
{
	char	**out;
	char	*str;
	int		start;
	int		end;
	int		k;
	int		wc;
}	t_split_data;

typedef struct s_redir
{
	int				fd_input;
	int				fd_output;
	int				type;
	char			*filename;
	char			*delimiter;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			*cmd;
	char			**cmd_args;
	int				count_args;
	char			*cmd_path;
	int				cmd_id;
	int				is_builtin;
	int				is_external;
	int				input_fd;
	int				output_fd;
	int				has_pipe;
	int				last_cmd;
	t_list			*redir_list;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	t_list			*first_cmd;
	char			**env_vars;
	char			**paths;
	int				pipe_input_fd;
	int				pipe_output_fd;
	int				cmd_count;
	int				is_running;
}	t_exec;

typedef struct s_mini
{
	int			bash_lvl;
	int			chars_in_line;
	t_list		*env;
	char		**envp_to_array;
	t_list		*tokens;
	t_exec		*exec;
	int			exit_status;
}	t_mini;

#endif
