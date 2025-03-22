#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // Llamada a fork para crear un proceso hijo
    pid_t pid = fork();

    // Verificar el valor de retorno para saber si es el padre o el hijo
    if (pid < 0) {
        // Si pid es negativo, significa que fork falló
        perror("Error al crear el proceso");
        return 1;
    } else if (pid == 0) {
        // Este bloque es ejecutado por el proceso hijo
        printf("proceso hijo. Mi PID es %d\n", getpid());
        printf("El PID de mi proceso padre es %d\n", getppid());
    } else {
        // Este bloque es ejecutado por el proceso padre
        printf("Soy el proceso padre. Mi PID es %d\n", getpid());
        printf("El PID de mi proceso hijo es %d\n", pid);
    }

    return 0;
}

