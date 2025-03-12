/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:28:32 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/11 23:50:19 by dasalaza         ###   ########.fr       */
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
/*   Updated: 2025/03/11 19:56:27 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
}

void	handle_signal_parent(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signal_child(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
	}
}

void	handle_exit(t_mini *minishell)
{
	int	last_exit_code;

	write(1, "exit\n", 5);
	last_exit_code = minishell->exit_status;
	rl_clear_history();
	free_mini(minishell);
	exit(last_exit_code);
}
