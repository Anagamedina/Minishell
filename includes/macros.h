/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/16 12:24:04 by dasalaza         ###   ########.fr       */
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
# define D_QUOTE '\"'
# define DOLLAR_SIGN '$'
# define QUESTION_MARK '?'
# define BACKSLASH '\\'

# define ECHO "echo"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define CD "cd"
# define PWD "pwd"
# define EXIT "exit"
//# define BUILT_LIST ECHO, EXPORT, UNSET, ENV, CD, PWD, EXIT, NULL
# define BUILT_LIST "echo", "export", "unset", "env", "cd", "pwd", "exit", NULL

#endif