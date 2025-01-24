/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:08:32 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/24 15:17:47 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "prototype.h"
# include <unistd.h>  // fork, pipe, dup2, execve, close, read, write
# include <stdlib.h>  // malloc, free, exit
# include <stdio.h>   // perror, printf
# include <fcntl.h>   // open
# include <sys/wait.h>  // wait, waitid
# include <sys/types.h>  // pid_t
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "macros.h"

typedef enum e_type_token
{
	WORD = 0,
	REDIR_IN,    //<     Representa la redirección de entrada '<'
	REDIR_ERR_OUT, //2>
	REDIR_ERR_APPEND, //2>>
	REDIR_APPEND, //>>
	REDIR_OUT, //>
	BUILTINS,
	CMD_EXTERNAL,
	DELIMITER,
	NULL_TYPE,
	PIPE,
	HEREDOC,
}					t_type_token;

/*
	ECHO,               // Builtin: echo
	CD,                 // Builtin: cd
	PWD,                // Builtin: pwd
	EXPORT,             // Builtin: export
*/
typedef struct s_tokens
{
    char            *str;
    t_type_token	type_token;
    size_t          length;
	int				id_token;
    struct s_tokens *next;
    struct s_tokens *prev;           // Puntero opcional al token anterior
}                   t_tokens;

typedef struct s_env
{
    char            *key;
    char            *value;
    char            *full_var;
    struct s_env    *next;
}                   t_env;

typedef struct	s_redir
{
	int 	fd_input;
	int 	fd_output;
	int 	type;
	char 	*filename;
	struct s_redir *next;
} 			t_redir;



typedef struct s_split_data
{
	char	**out;
	char	*str;
	int		start;
	int		end;
	int		k;       // Índice del token actual en el array
	int		wc;
}		t_split_data;

typedef struct pre_tokens
{
	int	*start;
	int	*end;
}		t_pre_tokens;

// t_pipex         *first_pipe;    // Estructura del primer pipe

typedef struct s_cmd
{
	char            *cmd;
	char            **cmd_args;
	int 			count_args;
	char 			*cmd_path;
	int             cmd_id;
	int     		is_builtin;
	int     		is_external;
	int            	input_fd;
	int             output_fd;
	//int 			exit_status;
	//t_pipe   		*pipes;
	//struct t_redir 	*redir_list;
	struct s_cmd    *next;
}				t_cmd;

typedef struct s_exec
{
	t_list          *first_cmd;
	char 			**env_vars;
	char			**paths;
	int				pipe_input_fd;
	int				pipe_output_fd;
	int             cmd_count;

}		t_exec;


typedef struct s_mini
{
    int             bash_lvl;       // Nivel de la shell
    int             chars_in_line;  // Contador de caracteres en línea de entrada
    t_list          *env;           // Variables de entorno
    t_list          *token;         // Lista de tokens
	t_exec			*exec;
    int             exit_status;    // Estado de salida del último comando ejecutado
    // char            *prompt;        // Prompt actual (opcional) ???
}                   t_mini;

#endif
