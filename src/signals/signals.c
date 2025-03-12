/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:28:32 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/12 18:41:25 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
int	restore_signal_to_default(int signal)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(signal, &sa, NULL) == -1)
		return (-1);
	return (0);
}
*/

static int	setup_here_doc_signals(void)
{
	signal(SIGINT, handle_signal_heredoc);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

static int	setup_parent_signals(void)
{
	signal(SIGINT, handle_signal_parent);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

static void	handle_sigquit_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

static int	setup_child_signals(void)
{
	signal(SIGINT, handle_signal_child);
	signal(SIGQUIT, handle_sigquit_child);
	return (1);
}

int	setup_signals(int mode, t_mini *mini)
{
	(void) mini;
	if (mode == PARENT)
		return (setup_parent_signals());
	else if (mode == CHILD)
		return (setup_child_signals());
	else if (mode == HERE_DOC)
		return (setup_here_doc_signals());
	return (-1);
}
