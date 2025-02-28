/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/22 18:19:43 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# include "prototype.h"
# include "minishell.h"

# define TRUE 1
# define FALSE 0

# define SEMICOLON 59
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define DOLLAR_SIGN '$'
# define QUESTION_MARK '?'
# define BACKSLASH '\\'
# define SPACE ' '
# define PIPE_CHAR '|'
# define TAB '\t'
# define NEWLINE '\n'

# define ECHO_VAR "echo"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define CD "cd"
# define PWD "pwd"
# define EXIT "exit"

# define PWD_ENV "PWD"
# define HOME_ENV "HOME"
# define USER_ENV "USER"
# define PATH_ENV "PATH"
# define PATH_DEF "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin"
# define HOME_DEFAULT "/home/"

# define OLDPWD_ENV "OLDPWD"
# define SHLVL "SHLVL"


/*--------------Signals-------------------*/
# define CTRL_C SIGINT
# define CTRL_D SIGQUIT
# define CTRL_SLASH SIGQUIT
# define CTRL_Z SIGTSTP
// Modes signals
# define PARENT 0
# define CHILD 1

/*--------------------Error messages-------------------*/
# define PRINT_SYNTAX_ERR_1 "syntax error near unexpected token `|'\n"
# define PRINT_SYNTAX_ERR_2 "syntax error near unexpected token `newline'\n"
# define PRINT_SYNTAX_ERR_3 "syntax error\n"

# define SHELL_LVL_WARNING "mini: warning: shell level too high, reset to 1\n"

# define MY_LLONG_MAX 9223372036854775807LL
# define MY_LLONG_MIN -9223372036854775808LL

#endif
