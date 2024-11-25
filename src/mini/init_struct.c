
#include "../../includes/minishell.h"

t_mini	*mini_list(char **envp)
{
    t_mini	*minishell;

    minishell = malloc(sizeof(t_mini));
    if (!minishell)
        return (NULL);
    minishell->bash_lvl = 0;
    minishell->chars_in_line = -1;
    minishell->cmds = NULL;
    minishell->env = init_env_list(envp); // Asigna la lista de variables de entorno
    minishell->exit_status = -1;
    minishell->token = NULL;
    if (!minishell->env)
    {
        free(minishell);
        printf("error con env ***********8.\n");
        return (NULL);
    }
    return (minishell);
}

void	print_mini(t_mini *mini)
{
    if (!mini)
    {
		printf("Estructura t_mini no inicializada.\n");
        return;
    }

    printf("=== Información de t_mini ===\n");
    printf("Bash Level: %d\n", mini->bash_lvl);
    printf("Chars in Line: %d\n", mini->chars_in_line);
    printf("Exit Status: %d\n", mini->exit_status);

    printf("\n--- Variables de Entorno ---\n");
    if (mini->env)
        print_env_list((t_list *)mini->env); // Implementar esta función
    else
        printf("No hay variables de entorno.\n");

    // printf("\n--- Tokens ---\n");
    if (mini->token)
        print_list_token((t_list *)mini->token); // Implementar esta función
    else
        printf("No hay tokens.\n");

    printf("\n--- Comandos ---\n");
    if (mini->cmds)
        print_list_token((t_list *)mini->cmds); // Implementar esta función
    else
        printf("No hay comandos.\n");
    

    printf("=== Fin de t_mini ===\n");
}
