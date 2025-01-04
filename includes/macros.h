/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/04 12:07:10 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
#define MACROS_H

# include "prototype.h"
# include "minishell.h"

# define TRUE 1
# define FALSE 0

# define SEMICOLON 59
# define S_QUOTE '\''
// # define S_QUOTE 39
# define D_QUOTE '\"'
# define DOLLAR_SIGN '$'
# define QUESTION_MARK '?'
# define BACKSLASH '\\'
# define SPACE ' '

# define ECHO "echo"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define CD "cd"
# define PWD "pwd"
# define EXIT "exit"


/*--------------------Error messages-------------------*/
# define PRINT_SYNTAX_ERR_1 "syntax error near unexpected token `|'\n"
# define PRINT_SYNTAX_ERR_2 "syntax error near unexpected token `newline'\n"
# define PRINT_SYNTAX_ERR_3 "syntax error\n"

#endif
