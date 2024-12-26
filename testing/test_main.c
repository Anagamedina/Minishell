//
// Created by daruuu on 12/24/24.
//

# include "unity.h"
# include "../includes/minishell.h"

t_mini	*g_minishell;

struct s_test
{
	char	*input;
	int 	expected;
}	t_test;

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

void clean_environment_testing(void)
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
	struct s_test tests[] = {
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
	while (i < sizeof(tests) / sizeof(tests[0]))
	{
		int	result = check_double_simple_dollar_case(tests[i].input);

		TEST_ASSERT_EQUAL(tests[i].expected, result);
		i++;
	}
}

void	test_check_double_simple_dollar_case_02(void)
{
	int	i;
	int	result;

	struct s_test	edge_cases[] =
	{
	{"\"  '   $HOME case not work' \"", TRUE},
	{"\"    $HOME case not work ' \"", TRUE},
	{"\"  '   $HOME case not work  \"", TRUE},
	{"\"'hello world'\"", FALSE},
	{"\"$HOME'case'\"", FALSE}
	};

	i = 0;
	while (i < sizeof(edge_cases) / sizeof(edge_cases[0]))
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

	char	*matrix_2d[5][2] =
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
	while (i < sizeof(matrix_2d) / sizeof(matrix_2d[0]))
	{
		result = replace_dollar_variable_skip_s_quote(matrix_2d[i][0], g_minishell->env);
		TEST_ASSERT_EQUAL_STRING(matrix_2d[i][1], result);
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
//	RUN_TEST(test_expand_vars_with_quotes_cases);
//	RUN_TEST(test_check_double_simple_dollar_case_01);
	RUN_TEST(test_check_double_simple_dollar_case_02);
	return (UNITY_END());
}
