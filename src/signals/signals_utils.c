/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:40:41 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/04 14:25:48 by catalinab        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		close(3);
		exit(EXIT_SUCCESS);
	}
}

void	handle_signal_parent(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signal_child(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
	}
}

int	configure_signal_handler(int signal, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	if (sigaction(signal, &sa, NULL) == -1)
	{
		perror("sigaction");
		return (-1);
	}
	return (0);
}
