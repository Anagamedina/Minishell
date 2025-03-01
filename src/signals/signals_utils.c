
#include "../../includes/minishell.h"

/* 📌 Configurar un manejador de señal */
int configure_signal_handler(int signal, void (*handler)(int))
{
	struct sigaction sa;

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
