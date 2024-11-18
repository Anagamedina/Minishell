#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*input;
	t_env	*test_env;
	t_list 	*tokens_list = NULL;

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
			printf("Error al leer el input\n");
			free(input);
			continue;
		}
//		caso: variable local de shell
		printf("--------------------\n");
		printf("check_var_local_input\n");
		printf("--------------------\n");
		check_var_local_input(input);
		printf("--------------------\n");
		tokens_list = generate_token_list(input);
//		if (!tokens_list)
//			printf("error token list\n");
		print_list_token(tokens_list);
	}
	return (0);
}
