/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/28 10:51:57 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_mini(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->env)
		free_env((t_env *)mini->env);
	if (mini->envp_to_array)
		free_string_matrix(mini->envp_to_array);
	if (mini->tokens)
		free_tokens(mini->tokens);
	/*if (mini->exec)
		free_exec(mini->exec);*/
	if (mini->exec)
	{
		if (mini->exec->first_cmd)
			free_cmd_list(mini->exec->first_cmd); // ✅ Esto ya maneja `free_redirections()`
		free_exec(mini->exec);
		free(mini);
	}
}
