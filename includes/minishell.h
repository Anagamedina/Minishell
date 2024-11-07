//
// Created by daruuu on 11/2/24.
//

#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>  // fork, pipe, dup2, execve, close, read, write
# include <stdlib.h>  // malloc, free, exit
# include <stdio.h>   // perror, printf
# include <fcntl.h>   // open
# include <sys/wait.h>  // wait, waitid
# include <sys/types.h>  // pid_t
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

#include "../utils/parsing.h"

typedef enum e_token_type
{
    WORD,           // Representa una palabra o comando
    PIPE,           // Representa el operador de tubería '|'
    REDIR_OUTPUT,   // Representa la redirección de salida '>'
    REDIR_INPUT,    // Representa la redirección de entrada '<'
    CONCAT_OUTPUT,   // Representa la redirección de concatenación '>>'
    NULL_TYPE       // Representa el final de la lista de tokens
}                   t_token_type;

//bonus libft
typedef struct s_tokens
{
    char            *str;            // Contenido del token
    t_token_type    token_type;      // Tipo del token
    size_t          length;          // Longitud de 'str' (opcional)
    struct s_tokens *next;
    struct s_tokens *prev;           // Puntero opcional al token anterior
}                   t_tokens;

//  
typedef struct s_env
{
    char            *key;            // Clave de la variable de entorno
    char            *value;          // Valor de la variable de entorno
    char            *full_var;       // Cadena completa "key=value" (opcional) ??
    struct s_env    *next;           // Puntero al siguiente nodo
}                   t_env;

// "wc -l" sería el comando y sus parámetros:
// cmd_args[0] = "wc"
// cmd_args[1] = "-l"
typedef struct s_cmd
{
    char            *cmd;           // Nombre del comando, ej. "wc"
    char            **cmd_args;     // Argumentos del comando
    int             cmd_id;         // ID del comando para orden en pipeline
    int             pipe[2];        // Descriptores para el pipe
    int             input_fd;       // Descriptor de archivo de entrada
    int             output_fd;      // Descriptor de archivo de salida
    int             flag_input_redir; // Flag para redirección de entrada
    int             flag_output_redir; // Flag para redirección de salida
    struct s_cmd    *next;          // Puntero al siguiente comando	
}				t_cmd;

typedef struct s_pipex
{
    t_cmd           *first_cmd;         // Primer comando en el pipeline
    t_env           *env_vars;          // Lista de variables de entorno
	int				pipe_input_fd;
	int				pipe_output_fd;
    int             cmd_count;          // Número de comandos en el pipeline

}				t_pipex;

typedef struct s_mini
{
    int             bash_lvl;       // Nivel de la shell
    int             chars_in_line;  // Contador de caracteres en línea de entrada
    t_env           *env;           // Variables de entorno
    t_tokens        *token;         // Lista de tokens
    t_pipex         *first_pipe;    // Estructura del primer pipe
    int             exit_status;    // Estado de salida del último comando ejecutado
    // char            *prompt;        // Prompt actual (opcional) ???
}                   t_mini;


#endif
