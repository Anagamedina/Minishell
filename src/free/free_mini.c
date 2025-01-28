/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:47:26 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/27 22:44:27 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_mini(t_mini *mini)
{
	if (!mini)
		return;
	if (mini->env)
		free_env((t_env *)mini->env);
	if (mini->token)
		free_tokens((t_tokens *)mini->token);
	if (mini->exec)
		free_exec(mini->exec);
	free(mini);
}
