/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 12:02:14 by catalinab         #+#    #+#             */
/*   Updated: 2025/03/11 10:32:06 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



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

static int	setup_child_signals(void)
{
	signal(SIGINT, handle_signal_child);
	return (1);
}


int	setup_signals(int mode)
{
	if (!isatty(STDIN_FILENO))
        return (0); 
	if (mode == PARENT)
		return (setup_parent_signals());
	else if (mode == CHILD)
		return (setup_child_signals());
	else if (mode == HERE_DOC)
		return (setup_here_doc_signals());
	return (-1);
}

















// int	restore_signal_to_default(int signal)
// {
// 	struct sigaction	sa;

// 	sa.sa_handler = SIG_DFL;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;
// 	if (sigaction(signal, &sa, NULL) == -1)
// 		return (-1);
// 	return (0);
// }

// static int	setup_here_doc_signals(void)
// {
// 	int	tmp_ignore;
// 	int	tmp_quit;

// 	tmp_quit = configure_signal_handler(SIGINT, handle_signal_heredoc);
// 	if (tmp_quit == -1)
// 		return (-1);
// 	tmp_ignore = configure_signal_handler(SIGQUIT, SIG_IGN);
// 	if (tmp_ignore == -1)
// 		return (-1);
// 	return (1);
// }

// static int	setup_parent_signals(void)
// {
// 	int	tmp;
// 	int	tmp1;

// 	tmp = configure_signal_handler(SIGINT, handle_signal_parent);
// 	if (tmp == -1)
// 		return (-1);
// 	// tmp1 = configure_signal_handler(SIGQUIT, SIG_IGN);
// 	if (signal(handle_signal_parent))
// 	{
// 		/* code */
// 	}
	
// 	// tmp1 = configure_signal_handler(SIGQUIT, SIG_IGN);
// 	if (tmp1 == -1)
// 		return (-1);
// 	return (1);
// }

// static int	setup_child_signals(void)
// {
// 	if (configure_signal_handler(SIGINT, handle_signal_child) == -1)
// 		return (-1);
	
// 	// if (restore_signal_to_default(SIGQUIT) == -1)
// 		return (-1);
// 	return (1);
// }

// void handle_signal_subshell(int sig)
// {
//     if (sig == SIGINT) 
// 	{
//         write(1, "\n", 1);
// 		// close(STDIN_FILENO); 
//         // exit(130);  // Termina el subshell y devuelve el código de salida 130
// 		// exit(130);
//     }
// }

// int	setup_subshell_signals() 
// {
// 	if (configure_signal_handler(SIGINT, handle_signal_subshell) == -1)
// 		return (-1);
// 	// if (configure_signal_handler(SIGQUIT, SIG_IGN) == -1)  // SIGQUIT se ignora en el subshell
// 	// 	return (-1);
// 	return (1);
// }

// // int	setup_signals(int mode, int bash_lvl)
// int	setup_signals(int mode)
// {
// 	if (!isatty(STDIN_FILENO))
//         return (0); 
// 	// if (bash_lvl > 1)
//     //     return setup_subshell_signals();  
		
// 	if (mode == PARENT)
// 		return (setup_parent_signals());
// 	else if (mode == CHILD)
// 		return (setup_child_signals());
// 	else if (mode == HERE_DOC)
// 		return (setup_here_doc_signals());
// 	else if (mode == SUBSHELL)
// 		return (setup_subshell_signals());
// 	return (-1);
// }
