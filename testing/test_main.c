//
// Created by daruuu on 12/24/24.
//

# include "unity.h"
# include "testing.h"
# include "../includes/minishell.h"

t_mini	*g_minishell;

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
	struct s_test_int test_cases[] = {
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
	int result;
	int	len = sizeof(test_cases) / sizeof(test_cases[0]);

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

	struct s_test_int	edge_cases[] = {

	{"\"  '   $HOME case not work' \"", TRUE},
	{"\"    $HOME case not work ' \"", TRUE},
	{"\"  '   $HOME case not work  \"", TRUE},
	{"\"'hello world'\"", FALSE},
	{"\"$HOME'case'\"", FALSE}
	};

	i = 0;
	int	len = sizeof(edge_cases) / sizeof(edge_cases[0]);
	while (i < len)
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

	struct s_test_str	matrix_cases[] =
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

void	test_sumar_a_mas_b(void)
{
	int	a = 5;
	int	b = 10;
	int result;

	result = sumar_a_b(a, b);

	TEST_ASSERT_EQUAL_INT(19, result);
}


/**
 * @brief Prueba remove_quotes_str.
 * @example remove_quotes_str("'  \$hello world'", S_QUOTE) => "  \$hello world"
 * @see remove_quotes_str
 */

void	test_01_remove_quotes_literals(void)
{
	struct s_test_str	t_literal_test_cases[] =
	{
		{"'$hei .!$%&/()=?a'", "$hei .!$%&/()=?a"}, // Cadena con caracteres comunes
		{"'|@#~{[]}\\_ abcd  0'", "|@#~{[]}\\_ abcd  0"},     // Combinación con caracteres especiales y alfanuméricos
		{"'Hello World!'", "Hello World!"},         // Frase sencilla con signos de exclamación
		{"'$1 + $2 = $3'", "$1 + $2 = $3"},         // Cadena con variables representadas como literales
		{"'[ASCII] #42'", "[ASCII] #42"},           // Caracteres de control con numeración
		{"'\\n\\t\\r literal'", "\\n\\t\\r literal"}, // Secuencias de escape tratadas como literales
		{"'A~B^C_D*E&F'", "A~B^C_D*E&F"},           // Uso de varios caracteres de la tabla ASCII
		{"'?$<>|:\"/'", "?$<>|:\"/"},                 // Caracteres de comparación y especiales
		{"'`echo test(`)'", "`echo test(`)"},           // Uso de backticks como literales
		{"'\\\"Quoted\\\"'", "\\\"Quoted\\\""}      // Cadena con comillas escapadas
	};

	int		i = 0;
	int		len_edge_cases = sizeof(t_literal_test_cases) / sizeof(t_literal_test_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// function on test
		result = remove_quotes_str(t_literal_test_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_literal_test_cases[i].input, t_literal_test_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_literal_test_cases[i].expected, result, message);
		free(result);
		i++;
	}
}

void	test_02_remove_quotes_general(void)
{

// Casos para cadenas literales generales
	struct s_test_str	t_literal_general_cases[] = {
			{"'$hei !·$%&/()=?a'", "$hei !·$%&/()=?a"},
			{"'$hei .!$%&/()=?a'", "$hei .!$%&/()=?a"},
			{"'|@#~{[]}\\abcd'", "|@#~{[]}\\abcd"}
	};

	int		i = 0;
	int		len_edge_cases = sizeof(t_literal_general_cases) / sizeof(t_literal_general_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// original function on test
		result = remove_quotes_str(t_literal_general_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_literal_general_cases[i].input, t_literal_general_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_literal_general_cases[i].expected, result, message);
		free(result);
		i++;
	}
}


void	test_03_remove_quotes_backslash(void)
{
// Casos para comillas escapadas
	struct s_test_str	t_escaped_quote_cases[] = {
			{"'\\$USER quote'", "\\$USER quote"},
			{"'  \\$USER quote  '", "  \\$USER quote  "},
			{"'\\$USER quote\\'", "\\$USER quote\\"},
			{"' \ \$USER quote\\'", " \ \$USER quote\\"},
			{"' \\\$USER quote \\\\'", " \\\$USER quote \\\\"},
			{"' \ \ \$USER quote \\\\'", " \ \ \$USER quote \\\\"}
	};

	int		i = 0;
	int		len_edge_cases = sizeof(t_escaped_quote_cases) / sizeof(t_escaped_quote_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// original function on test
		result = remove_quotes_str(t_escaped_quote_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_escaped_quote_cases[i].input, t_escaped_quote_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_escaped_quote_cases[i].expected, result, message);
		free(result);
		i++;
	}
}

void	test_04_remove_quotes_spaces(void)
{
// Casos con espacios y comillas simples normales
	struct s_test_str	t_space_handling_cases[] = {
			{"'   hello world'", "   hello world"},
			{"' spaced string '", " spaced string "},
			{"'   multiple   spaces   '", "   multiple   spaces   "}
	};

	int		i = 0;
	int		len_edge_cases = sizeof(t_space_handling_cases) / sizeof(t_space_handling_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// original function on test
		result = remove_quotes_str(t_space_handling_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_space_handling_cases[i].input, t_space_handling_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_space_handling_cases[i].expected, result, message);
		free(result);
		i++;
	}
}

void	test_05_remove_quotes_no_expand(void)
{
// Casos para variables sin expansión y escapes
	struct s_test_str	t_variable_and_escape_cases[] = {
			{"'$HOME'", "$HOME"},
			{"'   \\$HOME case '", "   \\$HOME case "}
	};

// Casos extremos o vacíos
	struct s_test_str	t_edge_cases[] = {
			{"''", ""},
			{"' '", " "},
			{"'\\'", "\\"}
	};

	int		i = 0;
	int		len_edge_cases = sizeof(t_variable_and_escape_cases) / sizeof(t_variable_and_escape_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// original function on test
		result = remove_quotes_str(t_variable_and_escape_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_variable_and_escape_cases[i].input, t_variable_and_escape_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_variable_and_escape_cases[i].expected, result, message);
		free(result);
		i++;
	}
}

void	test_06_remove_quotes_empty_cases(void)
{
// Casos extremos o vacíos
	struct s_test_str	t_edge_cases[] = {
			{"''", ""},
			{"' '", " "},
			{"'\\'", "\\"}
	};

	int		i = 0;
	int		len_edge_cases = sizeof(t_edge_cases) / sizeof(t_edge_cases[0]);
	char	*result;
	char	message[256];

	while (i < len_edge_cases)
	{
		// original function on test
		result = remove_quotes_str(t_edge_cases[i].input, S_QUOTE);

		snprintf(message, sizeof(message), \
		"FAILED ON CASE %d:               INPUT=[%s]" "   EXPECTED=[%s]   |" "   ACTUAL=[%s]",\
				i + 1, t_edge_cases[i].input, t_edge_cases[i].expected, result);

		TEST_ASSERT_EQUAL_STRING_MESSAGE(t_edge_cases[i].expected, result, message);
		free(result);
		i++;
	}
}


/*
 * heap: cuando usamos malloc, calloc, realloc, strdup, etc.
 * stack o pila: cuando declaramos variables locales.
 */

int	main(void)
{
	UNITY_BEGIN();
	// RUN_TEST(test_expand_vars_with_quotes_cases);
	// RUN_TEST(test_check_double_simple_dollar_case_01);
	// RUN_TEST(test_check_double_simple_dollar_case_02);
	RUN_TEST(test_01_remove_quotes_literals);
	RUN_TEST(test_02_remove_quotes_general);
	RUN_TEST(test_03_remove_quotes_backslash);
	RUN_TEST(test_04_remove_quotes_spaces);
	RUN_TEST(test_05_remove_quotes_no_expand);
	RUN_TEST(test_06_remove_quotes_empty_cases);
//	RUN_TEST(test_sumar_a_mas_b);
	return (UNITY_END());
}

