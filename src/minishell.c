
#include "../includes/minishell.h"

int main() {
	char *input;

	while (1) {
		// 1. Mostrar prompt y esperar el input del usuario
		printf("minishell> ");
		input = leer_input();
		if (!input) {
			fprintf(stderr, "Error al leer el input\n");
			continue;
		}

		// 2. Parsear el input
		if (parseo_exitoso(input)) {
			// Aquí deberías crear y manejar la lista de comandos
			// Suponiendo lista_comandos es un arreglo de cadenas
			char *lista_comandos[] = { "comando1", "comando2", NULL };  // Ejemplo, remplazar con lista real

			int i = 0;
			while (lista_comandos[i]) {
				pid_t pid = fork();
				if (pid == 0) {
					// Proceso hijo: ejecutar el comando
					ejecutar_comando(lista_comandos[i]);
					exit(EXIT_SUCCESS); // Termina el hijo exitosamente
				} else if (pid < 0) {
					// Error al crear el proceso
					perror("Error al crear proceso hijo");
				}
				i++;
			}

			// 4. Proceso padre espera a los hijos
			esperar_hijos();
		}

		// Liberar memoria del input
		free(input);
	}
	return 0;
}

//#include <stdio.h>
//#include <stdlib.h>
//#include <readline/readline.h>
//#include <readline/history.h>
//
//int main() {
//	char *input;
//
//	// Bucle de lectura de entrada
//	while (1) {
//		input = readline("minishell> "); // Muestra el prompt y lee la entrada
//
//		if (input == NULL) {
//			// Si el usuario presiona Ctrl+D, salimos del bucle
//			printf("\nExiting minishell.\n");
//			break;
//		}
//
//		if (*input) { // Si la entrada no está vacía
//			add_history(input); // Agrega la entrada al historial
//			printf("You entered: %s\n", input); // Muestra la entrada del usuario
//		}
//
//		free(input); // Liberamos la memoria asignada
//	}
//
//	return 0;
//}
