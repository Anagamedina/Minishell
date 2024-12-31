#ifndef TESTING_H
# define TESTING_H

# define UNITY_OUTPUT_COLOR
# include "unity.h"
# include "../includes/minishell.h"


#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"

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

// Functions to test remove_quotes_str
void    test_01_remove_quotes_literals(void);
void	test_02_remove_quotes_general(void);
void	test_03_remove_quotes_backslash(void);
void	test_04_remove_quotes_spaces(void);
void	test_05_remove_quotes_no_expand(void);
void	test_06_remove_quotes_empty_cases(void);



/**
 * Test the detection of the pattern: [" hello "abcd" "]
 * @see handle_double_quotes
 */
void	test01_double_quotes_keyboard_basic(void);


/**
 * @see check_double_simple_dollar_case
 */
void	test01_check_double_simple_dollar_case_int(void);


#endif
