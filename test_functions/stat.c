#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    struct stat fileStat;
    const char *filename = "archivo.txt";

    if (stat(filename, &fileStat) < 0) {
        perror("Error al obtener información del archivo");
        return 1;
    }

    printf("Información sobre el archivo %s:\\n\n", filename);
    printf("Tamaño: %ld bytes\\n\n", fileStat.st_size);
    printf("Permisos: %o\\n\n", fileStat.st_mode & 0777);
    printf("Última modificación: %ld\\n\n", fileStat.st_mtime);
    return 0;
}

