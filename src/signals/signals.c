/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:02:14 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/28 00:27:24 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * we can implement the signals (ctrl + C, ctrl + \, ctrl + D).
 * For ctrl + C, ctrl + \,
 * we can catch SIGINT and SIGQUIT respectively,
 * but in the case of ctrl + D we have to check the EOF or the end of string (i.e. NULL character).
*/
void	handle_sigint_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();	// crea una linea vacia nueva debajo de la actual
		rl_replace_line("", 0);	// reemplaza la linea actual con la cadena vacia
		rl_redisplay();		// redibuja la linea actual mostrando el prompt vacio
	}
}

/**
 * handle Ctrl + C
 * handle Ctrl + \ (ignoring signal)
 */
void	setup_signals(void)
{
	signal(SIGINT, handle_sigint_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}