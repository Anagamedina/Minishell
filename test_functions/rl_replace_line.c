
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    // Inicializamos un prompt
    char *prompt = "Ingrese comando> ";

    // Leemos una línea inicial
    char *linea = readline(prompt);
    
    // Mostramos la línea ingresada
    printf("Línea original: %s\n", linea);

    // Simulamos que queremos reemplazar la línea
    const char *nueva_linea = "comando corregido";
    
    // Usamos rl_replace_line para reemplazar la línea actual
    rl_replace_line(nueva_linea, 0);  // 0 indica que queremos mantener el undo
    rl_redisplay();                    // Redibuja la línea en pantalla

    // Imprimimos la línea modificada
    printf("Línea modificada: %s\n", nueva_linea);

    // Liberamos la memoria utilizada
    //free(linea); // Liberamos la memoria de la línea original

    return 0;
}

