#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0)
	{
        // Proceso hijo
        while (1)
		{
            printf("Proceso hijo ejecutándose...\\n");
            sleep(1);
        }
    }
	else
	{
        // Proceso padre
        sleep(3);  // Espera un momento
        kill(pid, SIGKILL);  // Termina el proceso hijo
        printf("Proceso hijo terminado.\\n");
    }
    return 0;
}

