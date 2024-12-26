//
// Created by daruuu on 12/24/24.
//
#define UNITY_INCLUDE_SETUP_STUBS

# include "unity.h"
# include "../includes/minishell.h"

t_mini	*g_minishell;

/**
 * Propósito
 * se utiliza para preparar el estado inicial para ejecutar cada prueba unitaria.
 * Es llamada automáticamente por el framework Unity antes de la ejecución de cada prueba.
 * Inicializar estructuras de datos, variables globales o recursos.
 * Crear un entorno limpio para cada prueba.
 * Evitar repetición de código común en las pruebas unitarias.
 */

void	setUp(void)
{
/*
	extern char **environ;
	g_minishell = init_mini_list(environ);
	TEST_ASSERT_NOT_NULL(g_minishell);
*/
}


/**
 * Se utiliza para limpiar o liberar los recursos utilizados por cada prueba unitaria.
 * Es llamada automáticamente por el framework Unity después de la ejecución de cada prueba.
 * Liberar memoria asignada dinámicamente.
 * Restaurar estados globales modificados durante la prueba.
 * Prevenir fugas de memoria o recursos compartidos contaminados entre pruebas.
 */

void	tearDown(void)
{
/*
	if (g_minishell && g_minishell->env)
		ft_lstclear((t_list **) g_minishell->env, free);
	free(g_minishell);
*/
}

/**
 * @brief When a valid variable is passed, it should replace the variable with the value
 * @see replace_dollar_variable_skip_s_quote
 */

void	test_replace_dollar_variable_skip_s_quote_with_valid_variable_replaces_correctly(void)
{
	t_list *env_list = NULL;
	t_env *env = malloc(sizeof(t_env));
	env->key = ft_strdup("USER");
	env->value = ft_strdup("daruuu");
	ft_lstadd_back(&env_list, ft_lstnew(env));

	char *token_rm_d_quote = ft_strdup("'$USER'");
	char *expected = ft_strdup("'daruuu'");

	char *result = replace_dollar_variable_skip_s_quote(token_rm_d_quote, env_list);

	TEST_ASSERT_EQUAL_STRING(expected, result);

	free(token_rm_d_quote);
	free(expected);
	free(result);
	ft_lstclear(&env_list, free);
}

int	main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_replace_dollar_variable_skip_s_quote_with_valid_variable_replaces_correctly);

	return UNITY_END();
}
