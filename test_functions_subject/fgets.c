#include <stdio.h>

int main() {
    // Abrimos el archivo en modo lectura
    FILE *archivo = fopen("ejemplo.txt", "r");
    
    // Verificamos que el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;  // Salimos del programa si hay un error
    }

    // Creamos un buffer para almacenar cada línea
    char linea[100];  // Ajusta el tamaño del buffer según tus necesidades

    // Leemos el archivo línea por línea
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);  // Imprime cada línea
    }

    // Cerramos el archivo
    fclose(archivo);

    return 0;
}

