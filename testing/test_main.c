//
// Created by daruuu on 12/24/24.
//

# include "unity.h"
# include "../includes/minishell.h"

t_mini	*g_minishell;

struct s_test_01
{
	char	*input;
	int 	expected;
}	t_test_01;

struct s_test_02
{
	char	*input;
	char	*expected;
}	t_test_02;

void	free_env_list(t_mini *minishell)
{
	if (g_minishell)
	{
		if (g_minishell->env)
		{
			t_list *current = g_minishell->env;
			t_list *next;

			while (current)
			{
				next = current->next;
				free(current->content);
				free(current);
				current = next;
			}
		}
		g_minishell->env = NULL;
	}
}

void	init_environment_testing(void)
{
	extern char **environ;

	g_minishell = init_mini_list(environ);
	TEST_ASSERT_NOT_NULL(g_minishell);
}

void	clean_environment_testing(void)
{
	free_env_list(g_minishell);
}


/**
 * @brief Inicializa el entorno global antes de cada prueba.
 *
 * Prepara `g_minishell` y su lista de entorno para evitar problemas de
 * estado compartido entre pruebas.
 */
void	setUp(void)
{
	init_environment_testing();
}

/**
 * @brief Limpia los recursos utilizados después de cada prueba.
 *
 * Libera los nodos de `g_minishell->env` y la estructura global
 * para prevenir fugas de memoria.
 */
void	tearDown(void)
{
	clean_environment_testing();
}

/**
 * @brief Prueba la detección del patron: [" ' $VAR ' "]
 *
 * Comprobar: d_quotes - s_quotes - dollar_sign
 *
 * @see check_double_simple_dollar_case
 */

void	test_check_double_simple_dollar_case_01(void)
{
	struct s_test_01 test_cases[] = {
			// Variable existente dentro de comillas simples
			{"\"'$USER hello world'\"", TRUE},

			// Variable inexistente dentro de comillas simples
			{"\"'$NON_EXISTENT_VAR hello'\"", TRUE},

			// Múltiples variables existentes e inexistentes dentro de comillas simples
			{"\"'hello $USER and $NON_EXISTENT_VAR world'\"", TRUE},

			// Variable especial ($SHLVL) junto a una inexistente dentro de comillas simples
			{"\"'$SHLVL test $NON_EXISTENT_VAR'\"", TRUE},

			// Espacios iniciales antes de una variable existente dentro de comillas simples
			{"\"   '  $this case works'\"", TRUE},

			// Espacios iniciales antes de una variable inexistente y mal formada (fuera de las comillas)
			{"\" ' $HOME case work '\"", FALSE},

			// Cadena completamente vacía
			{"''", FALSE},

			// Cadena sin ninguna variable presente
			{"'no dollar sign here'", FALSE},

			// Variable inexistente con un nombre largo pero válida sintácticamente
			{"'$NON_EXISTENT_VAR_LONG_LONG_LONG'", TRUE},
	};

	int i = 0;
<<<<<<< HEAD
	int result;
	int	len = sizeof(test_cases) / sizeof(test_cases[0]);
=======
	int	len_struct = sizeof(tests) / sizeof(tests[0]);
	while (i < len_struct)
	{
		int	result = check_double_simple_dollar_case(tests[i].input);
>>>>>>> 8fac052752966a655bac747b29664de5c920c2c0

	while (i < len)
	{
		result = check_double_simple_dollar_case(test_cases[i].input);
		TEST_ASSERT_EQUAL(test_cases[i].expected, result);
		i++;
	}
}

void	test_check_double_simple_dollar_case_02(void)
{
	int	i;
	int	result;

	struct s_test_01	edge_cases[] = {

	{"\"  '   $HOME case not work' \"", TRUE},
	{"\"    $HOME case not work ' \"", TRUE},
	{"\"  '   $HOME case not work  \"", TRUE},
	{"\"'hello world'\"", FALSE},
	{"\"$HOME'case'\"", FALSE}
	};

	i = 0;
<<<<<<< HEAD
	int	len = sizeof(edge_cases) / sizeof(edge_cases[0]);
	while (i < len)
=======
	int	len_struct = sizeof(edge_cases) / sizeof(edge_cases[0]);
	while (i < len_struct)
>>>>>>> 8fac052752966a655bac747b29664de5c920c2c0
	{
		result = check_double_simple_dollar_case(edge_cases[i].input);
		char	message[256];

		snprintf(message, sizeof(message), "Failed on case %d: input='%s'", i + 1, edge_cases[i].input);
		TEST_ASSERT_EQUAL_MESSAGE(edge_cases[i].expected, result, message);
//		TEST_ASSERT_EQUAL(edge_cases[i].expected, result);
		i++;
	}
}

/**
 * @brief Prueba la expansión de una variable válida.
 *
 * Cuando se pasa una variable válida, debe reemplazarla con el valor
 * correspondiente dentro de una cadena con comillas simples.
 * @see replace_dollar_variable_skip_s_quote
 */

/*
void	test_replace_dollar_var_when_valid_var_should_expand_correctly_version_01(void)
{
	char	*token_rm_d_quote = ft_strdup("'$USER hello world'");
	char	*expected = ft_strdup("'daruuu hello world'");
	char	*result = replace_dollar_variable_skip_s_quote(token_rm_d_quote, g_minishell->env);

	TEST_ASSERT_EQUAL_STRING(expected, result);
	free(token_rm_d_quote);
	free(expected);
	free(result);
}
*/
void	test_expand_vars_with_quotes_cases(void)
{
	int		i;
	char	*result;

	struct s_test_02	matrix_cases[] =
	{
	// Entrada con comillas simples y variable válida
	{"\"   '   $USER hello world'\"", "\"   '   daruuu hello world'\""},
			// Entrada con variable inexistente
	{"\"'$NON_EXISTENT_VAR hello'\"", "\"' hello'\""},
			// Entrada con múltiples variables
	{"\"'hello $USER and $NON_EXISTENT_VAR world'\"", "\"'hello daruuu and  world'\""},
			// Entrada con repetición de variables
	{"\"'$USER$USER$USER'\"", "\"'daruuudaruuudaruuu'\""},
			// Entrada con variable SHLVL
	{"\"'$SHLVL test $NON_EXISTENT_VAR'\"", "\"'0 test '\""}
	};

	i = 0;
	int	len = sizeof(matrix_cases) / sizeof(matrix_cases[0]);
	while (i < len)
	{
		result = replace_dollar_variable_skip_s_quote(matrix_cases[i].input, g_minishell->env);
		TEST_ASSERT_EQUAL_STRING(matrix_cases[i].expected, result);
		free(result);
		i++;
	}
}

<<<<<<< HEAD
/**
 * @brief Prueba remove_quotes_str.
 * @example remove_quotes_str("'  \$hello world'", S_QUOTE) => "  \$hello world"
 * @see remove_quotes_str
 */

=======
int	sumar(int a, int b)
{
	int result = a  + b;
	return (result);
}

void	test_sumar_a_mas_b(void)
{
	int	a = 5;
	int	b = 10;
	int result;

	result = sumar(a, b);

	TEST_ASSERT_EQUAL_INT(19, result);
}
>>>>>>> 8fac052752966a655bac747b29664de5c920c2c0

/*
 * heap: cuando usamos malloc, calloc, realloc, strdup, etc.
 * stack o pila: cuando declaramos variables locales.
 */

void	test_remove_quotes_str(void)
{

	// Casos correctos
	struct s_test_02	matrix_cases[] =
	{
		{"'hello world'", "hello world"},			// Comillas simples normales
		{" ' spaced string ' ", " spaced string "}, // Espacios alrededor de las comillas
		{"'\\'$USER quote\\''", "\\'$USER quote\\"}, // Comillas escapadas
		{"'   multiple   spaces   '", "   multiple   spaces   "}, // Múltiples espacios
		{"'$HOME'", "$HOME"},                      // Variable sin expansión
		{"'   \\$HOME case '", "   \\$HOME case"}, // Cadena con escape
		// Casos que deben fallar
		{"''", ""},                                // Comillas vacías
		{"' '", " "},                              // Espacio vacío entre comillas
		{"'\\", "'\\"},                            // Comilla escapada sin terminar
	};

	int		i = 0;
	int		len_edge_cases = sizeof(matrix_cases) / sizeof(matrix_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		snprintf(message, sizeof(message), "Failed on case %d: input=[%s]", i + 1, matrix_cases[i].input);

		result = remove_quotes_str(matrix_cases[i].input, S_QUOTE);
		TEST_ASSERT_EQUAL_STRING_MESSAGE(matrix_cases[i].expected, result, message);
		free(result); // Liberar memoria si es necesario
		i++;
	}
}

int	main(void)
{
	UNITY_BEGIN();
	// RUN_TEST(test_expand_vars_with_quotes_cases);
	// RUN_TEST(test_check_double_simple_dollar_case_01);
	// RUN_TEST(test_check_double_simple_dollar_case_02);
<<<<<<< HEAD

	RUN_TEST(test_remove_quotes_str);
=======
	RUN_TEST(sumar);
>>>>>>> 8fac052752966a655bac747b29664de5c920c2c0
	return (UNITY_END());
}
