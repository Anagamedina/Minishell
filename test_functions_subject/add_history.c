#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *linea;

    // Bucle para leer múltiples líneas de entrada
    while (1) {
        // Usamos readline para obtener la entrada del usuario
        linea = readline("Ingrese un comando (o 'exit' para salir): ");
        
        // Verificamos si el usuario quiere salir
        if (linea == NULL || strcmp(linea, "exit") == 0) {
            free(linea); // Liberamos la memoria
            break; // Salimos del bucle
        }

        // Agregamos la línea ingresada al historial
        add_history(linea);
        
        // Mostramos la línea ingresada
        printf("Línea ingresada: %s\n", linea);
        
        // Liberamos la memoria de la línea
        free(linea);
    }

    return 0;
}

