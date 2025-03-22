#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *ruta_archivo = "archivo.txt";
    int archivo;

    // Abre el archivo en modo escritura, lo crea si no existe y permite escribir al propietario
    archivo = open(ruta_archivo, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (archivo == -1) {
        perror("Error al abrir el archivo");
        return 1;
    }

    // Datos a escribir en el archivo
    const char *texto = "Hola, este es un ejemplo de escritura en un archivo.\n";
    ssize_t bytes_escritos = write(archivo, texto, strlen(texto));

    if (bytes_escritos == -1) {
        perror("Error al escribir en el archivo");
        close(archivo);
        return 1;
    }

    printf("Se han escrito %ld bytes en el archivo.\n", bytes_escritos);

    // Cerramos el archivo
    close(archivo);

    return 0;
}

