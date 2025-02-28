/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:02:14 by catalinab         #+#    #+#             */
/*   Updated: 2025/02/28 11:27:30 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @see rl_on_new_line  create a new line below the current one
 * @see rl_replace_line clear the current line
 * @see rl_redisplay redisplay the prompt clear
*/
void	handle_sigint_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
// Ctrl + D actualiza el mini->exit_status = 130