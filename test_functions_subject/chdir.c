#include <stdio.h>
#include <unistd.h>

int main() {
    if (chdir("/tmp") == 0) {
        printf("Directorio cambiado a /tmp\\n");
    } else {
        perror("Error al cambiar el directorio");
    }
    return 0;
}

