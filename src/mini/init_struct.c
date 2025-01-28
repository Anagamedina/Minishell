/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:28:10 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/28 16:01:00 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_mini	*init_mini_list(char **envp)
{
    t_mini	*minishell;

    minishell = malloc(sizeof(t_mini));
    if (!minishell)
        return (NULL);
    minishell->bash_lvl = 0;
    minishell->chars_in_line = -1;
    minishell->env = init_env_list(envp);
	// print_env_list(minishell->env);
    if (minishell->env == NULL)
    {
        fprintf(stderr, "Error: Failed to initialize environment list.\n");
        return (NULL);
    }
    minishell->token = NULL;
    minishell->exec = NULL;
    minishell->exit_status = -1;
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
    //printf("Exit Status: %d\n", mini->exit_status);

    printf("\n--- Variables de Entorno ---\n");
    if (mini->env)
        print_env_list((t_list *)mini->env); 
    else
        printf("No hay variables de entorno.\n");

    // printf("\n--- Tokens ---\n");
    if (mini->token)
        print_list_token((t_list *)mini->token); 
    else
        printf("No hay tokens.\n");

    printf("\n--- Comandos ---\n");
    if (mini->exec)
        print_list_token((t_list *)mini->exec);
    else
        printf("No hay comandos.\n");
    

    printf("=== Fin de t_mini ===\n");
}
