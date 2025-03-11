/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:01:04 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/11 06:33:10 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:15:57 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 20:07:43 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	configure_signal_handler(int signal, void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	if (sigaction(signal, &sa, NULL) == -1)
		return (-1);
	return (0);
}

//called from input.c
void	handle_exit(t_mini *minishell)
{
	int	last_exit_code;

	write(1, "exit\n", 5);
	last_exit_code = minishell->exit_status;
	rl_clear_history();
	free_mini(minishell);
	exit(last_exit_code);
}

void	handle_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		// g_signal_status = 1;
		write(1, "\n", 1);
		close(STDIN_FILENO);
		exit(1);
	}
}

/*
void	handle_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = 1;
		write(1, "\n", 1);
		// close(STDIN_FILENO);
	}
}
*/

/**
Si NO quieres usar una variable global (g_mini),
pasa minishell en setup_signals(), como en el siguiente paso.
*/
void	handle_signal_parent(int sig)
{
	if (sig == SIGINT)
	{
		// g_signal_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		// rl_redisplay();
		// rl_done = 1;
		// write(STDIN_FILENO, "\n", 1);
	}
}

void	handle_signal_child(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
	}
}
