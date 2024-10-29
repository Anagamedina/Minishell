#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Función manejadora para la señal SIGINT
void manejar_SIGINT(int signum) {
	signum = 1;
    printf("Señal SIGINT (Ctrl+C) capturada. Ignorando la interrupción.\n");
}

int main() {
    struct sigaction sa;

    // Configuración del manejador de la señal
    sa.sa_handler = manejar_SIGINT;   // Manejador de la señal SIGINT
    sigemptyset(&sa.sa_mask);         // No bloquear otras señales
    sa.sa_flags = SA_RESTART;         // Reinicia llamadas al sistema si son interrumpidas

    // Asignación del manejador a SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error al configurar sigaction");
        return 1;
    }

    printf("Presiona Ctrl+C para enviar SIGINT.\n");

    // Bucle infinito para mantener el programa activo
    while (1) {
        printf("Esperando señal...\n");
        sleep(2);
    }

    return 0;
}

