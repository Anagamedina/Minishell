#ifndef MACROS_H
#define MACROS_H

# include "prototype.h"
# include "minishell.h"

#define TRUE 1
#define FALSE 0
#define SEMICOLON 59
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define DOLLAR_SIGN '$'
# define QUESTION_MARK '?'
# define BACKSLASH '\\'


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