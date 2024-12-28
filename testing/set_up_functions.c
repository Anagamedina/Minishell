
# include "unity.h"
# include "testing.h"
# include "../includes/minishell.h"


// t_mini	*g_minishell;

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


int	sumar_a_b(int a, int b)
{
	return (a + b);
}