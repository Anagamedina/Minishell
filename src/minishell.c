#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
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
			// print_list_token(minishell->token);
		if (minishell->token == NULL)
			continue;
		//print_list_token(minishell->token);
		minishell->cmds = add_tokens_to_linked_list_commands(minishell->token);
		//print_list_commands(minishell->cmds);
		check_syntax_dollar(minishell);
		// cases_builtins(minishell);
	}
	return (0);
}
