#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    struct stat fileStat;
    int fd = open("archivo.txt", O_RDONLY);

    if (fd < 0) {
        perror("Error al abrir el archivo");
        return 1;
    }

    if (fstat(fd, &fileStat) < 0) {
        perror("Error al obtener información del archivo");
        close(fd);
        return 1;
    }

    printf("Tamaño: %ld bytes\\n", fileStat.st_size);
    close(fd);
    return 0;
}

