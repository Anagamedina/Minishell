/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:02:14 by catalinab         #+#    #+#             */
/*   Updated: 2025/03/09 01:42:09 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signal_heredoc(int sig)
{
	if (sig == SIGINT) // Si se presiona Ctrl+C
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
	}
}

void handle_signal_parent(int sig)
{
	if (sig == SIGINT)		// Ctrl+C en el shell
	{
		write(1, "\n", 1);
		rl_on_new_line();		// Indica que estamos en una nueva línea
		rl_replace_line("", 0);	// Borra la línea actual de readline
		rl_redisplay();			// Redibuja el prompt
	}
}

void handle_signal_child(int sig)
{
	if (sig == SIGINT) // Ctrl+C en un comando ejecutándose
	{
		write(2, "\n", 1);
	}
}

int setup_here_doc_signals(void)
{
	int	tmp = configure_signal_handler(SIGINT, handle_signal_heredoc);
	if (tmp == -1)
		return (-1);
	int	tmp1= configure_signal_handler(SIGQUIT, SIG_IGN);
	if ( tmp1 == -1)
		return (-1);
	return (1);
}


int setup_parent_signals(void)
{
	int	tmp = configure_signal_handler(SIGINT, handle_signal_parent);
	if (tmp == -1)
		return (-1);
	int	tmp1= configure_signal_handler(SIGQUIT, SIG_IGN);
	if ( tmp1 == -1)
		return (-1);
	return (1);
}

// static int restore_signal_to_default(int signal)
// {
// 	if (signal == SIGQUIT) // Solo restauramos señales que queramos manejar
// 	{
// 		if (sigaction(signal, &(struct sigaction){.sa_handler = SIG_DFL, .sa_flags = SA_RESTART}, NULL) == -1)
// 			return (-1);
// 	}
// 	return (0);
// }
int restore_signal_to_default(int signal)
{
	struct sigaction sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(signal, &sa, NULL) == -1)
		return (-1);
	return (0);
}

/* 📌 Configurar señales para procesos hijos */
int setup_child_signals(void)
{
	if (configure_signal_handler(SIGINT, handle_signal_child) == -1)
		return (-1);

	if (restore_signal_to_default(SIGQUIT) == -1) 
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
	else if (mode == HERE_DOC)
		return (setup_here_doc_signals());
	return (-1);
}