#include <stdio.h>

#define D_QUOTE '\"'
#define S_QUOTE '\''

/**
 * Avanza el índice `i` hasta encontrar la comilla de cierre correspondiente.
 * Si no encuentra una comilla de cierre, regresa -1 (error).
 */
int check_final_quote(const char *line, int *i, char quote) {
    (*i)++;
    while (line[*i] && line[*i] != quote)
        (*i)++;
    if (line[*i] == quote) {
        (*i)++;
        return (1); // Comillas emparejadas correctamente
    }
    return (-1); // Error: comilla de cierre no encontrada
}

/**
 * Calcula el número de palabras en una línea, manejando comillas simples y dobles.
 * Palabras entre comillas cuentan como un solo token.
 */
int get_size_words_with_pivote(const char *line) {
    int i = 0;
    int word_count = 0;

    while (line[i] != '\0') {
        // Ignorar espacios en blanco
        while (line[i] == ' ' || line[i] == '\t')
            i++;

        // Si encontramos comillas dobles
        if (line[i] == D_QUOTE) {
            if (check_final_quote(line, &i, D_QUOTE) == -1) {
                printf("Error: comilla doble sin cerrar.\n");
                return (-1);
            }
            word_count++;
        }
        // Si encontramos comillas simples
        else if (line[i] == S_QUOTE) {
            if (check_final_quote(line, &i, S_QUOTE) == -1) {
                printf("Error: comilla simple sin cerrar.\n");
                return (-1);
            }
            word_count++;
        }
        // Si encontramos texto sin comillas
        else if (line[i] != '\0') {
            while (line[i] && line[i] != ' ' && line[i] != '\t' \
                   && line[i] != D_QUOTE && line[i] != S_QUOTE)
                i++;
            word_count++;
        }
    }
    return word_count;
}

/**
 * Ejemplo de uso
 */
int main() {
    const char *line = "echo \"\" hello \"\" world 'test'";
    int word_count = get_size_words_with_pivote(line);

    if (word_count != -1)
        printf("Número de palabras: %d\n", word_count);
    else
        printf("Error en el análisis de la línea.\n");

    return 0;
}

