/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:02:14 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/28 00:40:34 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//#include "../includes/minishell.h"
#include "../../includes/minishell.h"


void handle_signal_parent(int sig)
{
	if (sig == SIGINT) // Ctrl+C en el shell
	{
		write(2, "\n", 1);
		rl_on_new_line();       // Indica que estamos en una nueva línea
		//rl_replace_line("", 0); // Borra la línea actual de readline
		rl_redisplay();         // Redibuja el prompt
	}
}

/* 📌 Manejar señales en los procesos hijos */
void handle_signal_child(int sig)
{
	if (sig == SIGINT) // Ctrl+C en un comando ejecutándose
	{
		write(2, "\n", 1);
	}
}

/* 📌 Configurar señales para el shell */
int setup_parent_signals(void)
{
	if (configure_signal_handler(SIGINT, handle_signal_parent) == -1)
		return (-1);
	if (configure_signal_handler(SIGQUIT, SIG_IGN) == -1)
		return (-1);
		return (1);
}

/* 📌 Configurar señales para procesos hijos */
int setup_child_signals(void)
{
	if (configure_signal_handler(SIGINT, handle_signal_child) == -1)
		return (-1);
	if (configure_signal_handler(SIGQUIT, SIG_IGN) == -1)
		return (-1);
		return (1);
}

/* 📌 Llamar a la función correcta según el contexto */
int setup_signals(int mode)
{
	if (mode == PARENT)
		return (setup_parent_signals());
	else if (mode == CHILD)
		return (setup_child_signals());
	return (-1);
}




/*
After finishing the execution, we can implement the signals (ctrl + C, ctrl + \, ctrl + D).

For ctrl + C, ctrl + \,
we can catch SIGINT and SIGQUIT respectively, 
but in the case of ctrl + D we have to check the EOF or the end of string (i.e. NULL character).
*/

/*
void	handle_signal_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();	// crea una linea vacia nueva debajo de la actual
	//rl_replace_line("", 0);	// reemplaza la linea actual con la cadena vacia
	rl_redisplay();		// redibuja la linea actual mostrando el prompt vacio
}*/

/*
void	handle_signal_ctrl_slash(int sig)
{
	(void)sig;
	write(1, "\b\b  \b\b", 6);
}
*/