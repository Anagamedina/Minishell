/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:02:14 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/12 12:04:36 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

/*
After finishing the execution, we can implement the signals (ctrl + C, ctrl + \, ctrl + D).

For ctrl + C, ctrl + \,
we can catch SIGINT and SIGQUIT respectively, 
but in the case of ctrl + D we have to check the EOF or the end of string (i.e. NULL character).
*/
void	handle_signal_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();	// crea una linea vacia nueva debajo de la actual
	//rl_replace_line("", 0);	// reemplaza la linea actual con la cadena vacia
	rl_redisplay();		// redibuja la linea actual mostrando el prompt vacio
}

/*
void	handle_signal_ctrl_slash(int sig)
{
	(void)sig;
	write(1, "\b\b  \b\b", 6);
}
*/