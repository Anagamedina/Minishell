/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:08:32 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/08 10:40:44 by  dasalaza        ###   ########.fr       */
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
	REDIR_IN,        // Representa la redirección de entrada '<'
	CONCAT_OUT,      // Representa la redirección de concatenación '>>'
	REDIR_ERR_OUT,
	REDIR_ERR_APPEND,
	REDIR_APPEND,
	REDIR_OUT,
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


// "wc -l" sería el comando y sus parámetros:
// cmd_args[0] = "wc"
// cmd_args[1] = "-l"
typedef struct s_cmd
{
    char            *cmd;           // Nombre del comando, ej. "wc"
    char            **cmd_args;     // Argumentos del comando (por ejemplo, ["echo", "hello"])
	int 			count_args;		// Numero de argumentos del comando
    int             cmd_id;         // ID del comando para orden en pipeline
	struct t_redir 		*redir_list;    // Lista de redirecciones asociadas al comando
    int             pipe[2];        // Descriptores para el pipe
    int             input_fd;       // Descriptor de archivo de entrada
    int             output_fd;      // Descriptor de archivo de salida
    struct s_cmd    *next;          // Puntero al siguiente comando
}				t_cmd;

typedef struct s_mini
{
    int             bash_lvl;       // Nivel de la shell
    int             chars_in_line;  // Contador de caracteres en línea de entrada
    t_list          *env;           // Variables de entorno
    t_list          *token;         // Lista de tokens
    t_list          *cmds;         // Lista de commands 
    int             exit_status;    // Estado de salida del último comando ejecutado
    // char            *prompt;        // Prompt actual (opcional) ???
}                   t_mini;

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

#endif

/*typedef struct s_pipe
{
    t_cmd           *first_cmd;         // Primer comando en el pipeline
    t_env           *env_vars;          // Lista de variables de entorno
	//char			*path;
	//int 			error;
	int				pipe_input_fd;
	int				pipe_output_fd;
    int             cmd_count;          // Número de comandos en el pipeline

}				t_pipe;*/
