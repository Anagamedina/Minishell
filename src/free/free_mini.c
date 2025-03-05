/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:49:36 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/05 19:04:00 by dasalaza         ###   ########.fr       */
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
	t_list	*tmp;

    if (!mini)
    {
    	return ;
    }
	rl_clear_history();
    while (mini->env)
    {
        tmp = mini->env->next;
        t_env *env = (t_env *)mini->env->content;
        if (env)
        {
            free(env->key);
            free(env->value);
            free(env->full_var);
            free(env);
        }
        free(mini->env);
        mini->env = tmp;
    }
    // Liberar tokens
    while (mini->tokens)
    {
        tmp = mini->tokens->next;
        t_tokens *token = (t_tokens *)mini->tokens->content;
        if (token)
        {
            free(token->str);
            free(token);
        }
        free(mini->tokens);
        mini->tokens = tmp;
    }

    // Liberar envp_to_array
    if (mini->envp_to_array)
    {
        int i = 0;
        while (mini->envp_to_array[i])
        {
            free(mini->envp_to_array[i]);
            i++;
        }
        free(mini->envp_to_array);
    }

    // Liberar estructura exec
    if (mini->exec)
        free_exec(mini->exec);

    // Liberar la estructura principal
    free(mini);
}
