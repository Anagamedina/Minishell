#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h> // Para usar sleep()

int main() {
    // Inicializamos el prompt
    char *prompt = "Comando> ";

    // Leemos la línea inicial
    char *linea = readline(prompt);
    printf("Línea original: %s\n", linea);

    // Simulamos un cambio en el prompt después de 3 segundos
    sleep(3);
    prompt = "NuevoPrompt> ";
    
    // Reemplazamos la línea actual por un nuevo texto
    rl_replace_line("Nueva línea ingresada", 0); // Reemplaza la línea actual
    rl_on_new_line();                             // Indica que estamos en una nueva línea
    rl_redisplay();                               // Redibuja la línea con el nuevo prompt

    // Leemos otra línea con el nuevo prompt
    char *nueva_linea = readline(prompt);

    if (nueva_linea) {
        printf("Línea ingresada: %s\n", nueva_linea);
        //free(nueva_linea); // Liberamos la memoria de la nueva línea
    }

    // Liberamos la memoria de la línea original
    free(linea);

    return 0;
}

