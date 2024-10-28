#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h> // Para usar sleep()

int main() {
    // Definimos un prompt inicial
    char *prompt = "Comando> ";

    // Leemos una línea con readline usando el prompt inicial
    char *linea = readline(prompt);

    // Simulamos que se cambia el prompt después de 3 segundos
    sleep(3);
    prompt = "NuevoPrompt> ";
    
    // Indicamos a readline que debe refrescar la línea y el prompt
    rl_on_new_line();         // Marca la nueva línea
    rl_replace_line("", 0);   // Limpia la línea actual
    rl_redisplay();           // Redibuja el prompt y la línea

    // Continuamos leyendo otra línea con el nuevo prompt
    linea = readline(prompt);

    if (linea) {
        printf("Línea ingresada: %s\n", linea);
        //free(linea); // Liberamos la memoria de la línea
    }

    return 0;
}

