#include <stdio.h>
#include <unistd.h>

int main() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Directorio actual: %s\\n", cwd);
    } else {
        perror("Error al obtener el directorio actual");
    }
    return 0;
}

