/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:49:36 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/09 01:06:53 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*void	free_mini(t_mini *mini)
{
	t_list	*tmp;

    if (!mini)
        return;
    if (mini->env)
    {
        while (mini->env)
        {
            tmp = mini->env->next;
            free(((t_env *)mini->env->content)->key);
            free(((t_env *)mini->env->content)->value);
            free(mini->env->content);
            free(mini->env);
            mini->env = tmp;
        }
    }
    if (mini->tokens)
    {
        while (mini->tokens)
        {
            tmp = mini->tokens->next;
            free(((t_tokens *)mini->tokens->content)->str);
            free(mini->tokens->content);
            free(mini->tokens);
            mini->tokens = tmp;
        }
    }
    if (mini->exec)
        free_exec(mini->exec);
    free(mini);
}*/

void	free_mini(t_mini *mini)
{
    if (!mini)
    {
    	return ;
    }
	// rl_clear_history();
    if (mini->tokens)
    {
    	free_tokens_list(&mini->tokens);
        // free(mini->tokens);
    }

    // Liberar estructura exec
    if (mini->exec)
    {
    	mini->exec->is_running = 0;
        free_exec(mini->exec);
    	// mini->exec = NULL;
    }

    if (mini->envp_to_array)
    {
    	free_string_matrix(mini->envp_to_array);
    	// mini->envp_to_array = NULL;
    }

    if (mini->env)
    {
    	free_env_list(&mini->env);
        // free(mini->env);
    }
    // Liberar la estructura principal
    free(mini);
}
