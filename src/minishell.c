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
		// if (!minishell->token)
		// continue;
		print_list_token(minishell->token);

		// printf("********** CREATE EACH COMMAND:\n");
		minishell->cmds = add_tokens_to_linked_list_commands(minishell->token);
		printf("********** PRINT EACH COMMAND:\n");
		print_list_commands(minishell->cmds);
		printf("********** cases builtins :\n");

		cases_builtins(minishell);

    	// t_cmd   *token_02;




    	// token_02 = minishell->token->next->content;
    	// printf("token 02 : %s\n", token_02->cmd);

    	// if ((ft_strcmp((char *)cmd_01->, "export") == 0) && (token_02 != NULL) )
    	// {
        // 	printf("entro en export:\n");
        // 	init_process_export(mini->token, mini->env);
    	// }

	}
	return (0);
}
