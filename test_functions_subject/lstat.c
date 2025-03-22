#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    struct stat linkStat;
    const char *linkname = "enlace_simbólico";

    if (lstat(linkname, &linkStat) < 0) {
        perror("Error al obtener información del enlace simbólico");
        return 1;
    }

    printf("Tamaño del enlace simbólico: %ld bytes\\n", linkStat.st_size);
    return 0;
}

