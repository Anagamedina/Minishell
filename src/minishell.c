#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*input;
	t_env	*test_env;
//	t_list 	*tokens_list = NULL;

	test_env = get_env(envp);
	if (!test_env)
	{
		fprintf(stderr, "Error al inicializar la lista de variables de entorno.\n");
		return (EXIT_FAILURE);
	}
	while (1)
	{
		input = read_input();
		if (!input || !check_quotes_line(input))
		{
			// printf(stderr, "Error al leer el input\n");
			printf("Error al leer el input\n");
//			printf("Error: Unmatched quotes in the line.\n");
			continue;
		}
//		check_var_local_input(input);
//		tokens_list = generate_token_list(input);
//		print_list_token(tokens_list);
	}
	return (0);
}
