#ifndef TESTING_H
# define TESTING_H

# include "unity.h"
# include "../includes/minishell.h"

extern t_mini	*g_minishell;

typedef struct s_test_int
{
    char    *input;     // Entrada del caso de prueba
    int     expected;   // Resultado esperado (entero)
}   t_test_int;

typedef struct s_test_str
{
    char    *input;     // Entrada del caso de prueba
    char    *expected;  // Resultado esperado (cadena)
}   t_test_str;

// Funciones de configuración del entorno de testing
void    init_environment_testing(void);  // Inicializa el entorno para pruebas
void    clean_environment_testing(void); // Limpia el entorno de pruebas
void    free_env_list(void); // Libera recursos asociados al entorno

// Funciones auxiliares de testing
int     sumar_a_b(int a, int b);

#endif
