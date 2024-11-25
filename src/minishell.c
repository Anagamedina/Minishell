#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	char	*input = NULL; // Inicializar input a NULL
	t_env	*test_env;
	t_list 	*locals = NULL;

	t_list 	*tokens_list = NULL;
	test_env = (t_env *)init_env_list(envp);
/*
	if (!test_env)
	{
		printf("Error al inicializar la lista de variables de entorno.\n");
		return (EXIT_FAILURE);
	}
*/
	while (1)
	{
		input = read_input();
		if (!input || !check_quotes_line(input))
		{
			printf("Error al leer el input\n");
			free(input);
			continue;
		}
		tokens_list = generate_token_list(input);
		if (!tokens_list)
			printf("error token list\n");

		printf("--------------------------------------\n");
		printf("**********PRINT LIST TOKENS:\n");
		print_list_token(tokens_list);
		printf("--------------------------------------\n");

//		printf("********** FUNCTION TO ADD CREATE EACH COMMAND:\n");
//		t_list *commands_list = add_tokens_to_linked_list_commands(tokens_list);
		printf("--------------------------------------------\n");
//		printf("********** PRINT LIST COMMANDS:\n");
//		print_list_commands((t_list *) commands_list);

//		printf("********** BUILTIN-EXPORT ***********\n");
//		if (commands_list->content)
//		{
//			builtin_export((t_list **)  commands_list, (t_list **)test_env, &locals);
//		}

	}
	return (0);
}
