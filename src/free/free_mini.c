/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:49:36 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/10 01:21:50 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*rl_clear_history();*/
void	free_mini(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->tokens)
	{
		free_tokens_list(&mini->tokens);
	}
	if (mini->exec)
	{
		mini->exec->is_running = 0;
		free_exec(mini->exec);
	}
	if (mini->envp_to_array)
	{
		free_string_matrix(mini->envp_to_array);
	}
	if (mini->env)
	{
		free_env_list(&mini->env);
	}
	free(mini);
}
