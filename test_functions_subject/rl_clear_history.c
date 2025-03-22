#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

// gcc ejemplo.c -o ejemplo -lreadline

int main() {
    // Agregamos algunas líneas al historial
    add_history("Primer comando");
    add_history("Segundo comando");
    add_history("Tercer comando");
    add_history("hello ");

    // Mostramos el número de elementos en el historial
    printf("Número de comandos en el historial: %d\n", history_length);

    // Limpiamos el historial
    rl_clear_history();

    // Verificamos que el historial está vacío
    printf("Número de comandos después de limpiar el historial: %d\n", history_length);

    return 0;
}

