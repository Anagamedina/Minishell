/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:02:14 by catalinab         #+#    #+#             */
/*   Updated: 2025/03/04 11:40:28 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_parent_signals(void)
{
	int	tmp;
	int	tmp1;

	tmp = configure_signal_handler(SIGINT, handle_signal_parent);
	if (tmp == -1)
		return (-1);
	tmp1= configure_signal_handler(SIGQUIT, SIG_IGN);
	if (tmp1 == -1)
		return (-1);
	return (1);
}

int	setup_child_signals(void)
{
	int	tmp;

	tmp = configure_signal_handler(SIGINT, handle_signal_child);
	if (tmp == -1)
		return (-1);
	if (configure_signal_handler(SIGQUIT, SIG_IGN) == -1)
		return (-1);
	return (1);
}

int	setup_signals(int mode)
{
	if (mode == PARENT)
		return (setup_parent_signals());
	else if (mode == CHILD)
		return (setup_child_signals());
	return (-1);
}
