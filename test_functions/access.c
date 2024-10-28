#include <stdio.h>
#include <unistd.h>

int main() {
    const char *ruta_archivo = "archivo.txt"; // Nombre del archivo a verificar

    // Verificamos si el archivo existe
    if (access(ruta_archivo, F_OK) == 0) {
        printf("El archivo '%s' existe.\n", ruta_archivo);
        
        // Verificamos si se puede leer el archivo
        if (access(ruta_archivo, R_OK) == 0) {
            printf("El archivo '%s' se puede leer.\n", ruta_archivo);
        } else {
            printf("No se tiene permiso para leer el archivo '%s'.\n", ruta_archivo);
        }
        
        // Verificamos si se puede escribir en el archivo
        if (access(ruta_archivo, W_OK) == 0) {
            printf("El archivo '%s' se puede escribir.\n", ruta_archivo);
        } else {
            printf("No se tiene permiso para escribir en el archivo '%s'.\n", ruta_archivo);
        }
    } else {
        printf("El archivo '%s' no existe.\n", ruta_archivo);
    }

    return 0;
}

