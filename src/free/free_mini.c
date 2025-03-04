/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:49:36 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/04 23:05:17 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_mini(t_mini *mini)
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
}