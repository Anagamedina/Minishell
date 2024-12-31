/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:08:32 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/27 12:39:18 by anamedin         ###   ########.fr       */
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

//bonus libft
//echo -n abcd
//cat
//-n
//abcd

typedef enum e_type_token
{
	WORD = 0,           // Representa una palabra o comando genéricoREDIR_OUTPUT,       // Representa la redirección de salida '>'
	REDIR_IN,    //<     Representa la redirección de entrada '<'
	REDIR_ERR_OUT, //2>
	REDIR_ERR_APPEND, //2>>
	REDIR_APPEND, //>>
	REDIR_OUT, //>
	BUILTINS,
	DELIMITER,			// Para manejar ';'
	NULL_TYPE,     // Representa el final de la lista de tokens
	PIPE,                // Representa el operador de tubería '|'
}					t_type_token;
//	ECHO,               // Builtin: echo
//	CD,                 // Builtin: cd
//	PWD,                // Builtin: pwd
//	EXPORT,             // Builtin: export

typedef struct s_tokens
{
    char            *str;            // Contenido del token
    t_type_token	type_token;      // Tipo del token
    size_t          length;          // Longitud de 'str' (opcional)
	int				id_token;			// Identificador del token
    struct s_tokens *next;
    struct s_tokens *prev;           // Puntero opcional al token anterior
}                   t_tokens;

typedef struct s_env
{
    char            *key;            // Clave de la variable de entorno
    char            *value;          // Valor de la variable de entorno
    char            *full_var;       // Cadena completa "key=value" (opcional) ??
    struct s_env    *next;           // Puntero al siguiente nodo
}                   t_env;

typedef struct	s_redir
{
	int 	fd_input;            // Descriptor de archivo de entrada
	int 	fd_output;           // Descriptor de archivo de salida
	int 	type;                // Tipo de redirección (por ejemplo, REDIR_INPUT, REDIR_OUTPUT)
	char 	*filename;          // Nombre del archivo de redirección
	struct s_redir *next;    // Puntero al siguiente nodo de redirección
} 			t_redir;

//tokens indivuales
typedef struct s_split_data
{
	char	**out;
	char	*str;
	int		start;
	int		end;
	int		k;       // Índice del token actual en el array
	int		wc;
}		t_split_data;

// "wc -l" sería el comando y sus parámetros:
// cmd_args[0] = "wc"
// cmd_args[1] = "-l"
typedef struct s_cmd
{
	char            *cmd;
	char            **cmd_args;
	int 			count_args;
	int             cmd_id;
	int     		is_builtin;
	struct t_redir 		*redir_list;
	int             pipe[2];        // Descriptores para el pipe
	int             input_fd;       // Descriptor de archivo de entrada
	int             output_fd;      // Descriptor de archivo de salida
	//int 			exit_status;
	struct s_cmd    *next;
}				t_cmd;

typedef struct s_exec
{
    t_list           *first_cmd;         // Primer comando en el pipeline
    t_list 			*env_vars;          	// Lista de variables de entorno
	char			**paths;             //array de rutas de posibles ubi de comandos
	int				pipe_input_fd;
	int				pipe_output_fd;
    int             cmd_count;          // Número de comandos en el pipeline
	//int 			error;
	//char			**env;
	//char			**argvs;  			//argumentos del programa

}				t_exec;


typedef struct s_mini
{
	int             bash_lvl;
	int             chars_in_line;
	t_list          *env;
	t_list          *token;         // Lista de tokens
	//t_list          *cmd;
	int             exit_code;
	struct s_exec 	*exec;
}                   t_mini;

#endif
