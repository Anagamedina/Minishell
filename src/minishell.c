#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) argv;
	// (void) envp;

	char	*input = NULL; 

	t_mini	*minishell;

	minishell = NULL;
	minishell = mini_list(envp);
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
		if (!minishell->token)
			printf("error token list\n");
		print_list_token(minishell->token);
		printf("--------------------------------------\n");

		printf("********** CREATE EACH COMMAND:\n");
		minishell->cmds = add_tokens_to_linked_list_commands((t_list *)minishell->token);
		cases_builtins(minishell->cmds, minishell->env);

	}
	return (0);
}
