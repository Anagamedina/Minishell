#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void)	argv;
	char	*input = NULL; 
	t_mini	*minishell;

	minishell = init_mini_list(envp);

	if (!minishell)
 	{
        printf("Error al inicializar minishell.\n");
        return (1);
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
		minishell->token = generate_token_list(input);
		if (minishell->token == NULL)
			continue;
		parser_tokens(minishell);

//		minishell->cmds = add_tokens_to_linked_list_commands(minishell->token);
		//print_list_commands(minishell->cmds);
		print_list_token(minishell->token);
		// cases_builtins(minishell);
	}
	return (0);
}
