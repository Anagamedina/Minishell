#ifndef MACROS_H
#define MACROS_H

# include "prototype.h"
# include "minishell.h"

#define TRUE 1
#define FALSE 0


// Lista de comandos built-ins
# define BUILTINS_LIST \
    {                  \
        "echo",        \
        "export",      \
        "unset",       \
        "env",         \
        "cd",          \
        "pwd",         \
        "exit",        \
        NULL           \
    }

#endif