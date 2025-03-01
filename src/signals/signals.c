/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: catalinab <catalinab@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:02:14 by catalinab         #+#    #+#             */
/*   Updated: 2025/03/01 13:28:35 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signal_heredoc(int sig)
{
	if (sig == SIGINT) // Si se presiona Ctrl+C
	{
		write(2, "\n", 1);
		exit(1); // Finaliza el proceso del heredoc
	}
}

void	handle_signal_parent(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		if (isatty(STDIN_FILENO)) // Verifica si `readline` está en uso
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void handle_signal_child(int sig)
{
	if (sig == SIGINT) // Ctrl+C en un comando ejecutándose
	{
		write(2, "\n", 1);
	}
}

int setup_heredoc_signals(void)
{
	if (configure_signal_handler(SIGINT, handle_signal_heredoc) == -1)
		return (-1);
	if (configure_signal_handler(SIGQUIT, SIG_IGN) == -1)
		return (-1);
	return (0);
}


int setup_parent_signals(void)
{
	if (configure_signal_handler(SIGINT, handle_signal_parent) == -1)
		return (-1);
	if (configure_signal_handler(SIGQUIT, SIG_IGN) == -1)
		return (-1);
	return (0);
}

int setup_child_signals(void)
{
	if (configure_signal_handler(SIGINT, handle_signal_child) == -1)
		return (-1);
	if (configure_signal_handler(SIGQUIT, SIG_IGN) == -1)
		return (-1);
	return (0);
}

/* 📌 Llamar a la función correcta según el contexto */
int setup_signals(int mode)
{
	if (mode == PARENT)
		return (setup_parent_signals());
	if (mode == CHILD)
		return (setup_child_signals());
	if (mode == HERE_DOC) // Heredoc
		return (setup_heredoc_signals());
	return (-1);
}
