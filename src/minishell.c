#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*input;
	t_env	*test_env;

	test_env = get_env(envp);
//	print_env_list(test_env);
	if (!test_env)
	{
		fprintf(stderr, "Error al inicializar la lista de variables de entorno.\n");
		return (EXIT_FAILURE);
	}

	while (1)
	{
		input = read_input();
		if (!input)
		{
			// printf(stderr, "Error al leer el input\n");
			printf("Error al leer el input\n");
			continue;
		}

	}
	//Parsear el input
	/*if (check_syntax(ietput))
	{

	}*/
	return (0);
}
