/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:47:26 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/03 19:54:10 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_mini(t_mini *mini)
{
	if (!mini)
		return ;
	if (mini->env)
		free_env((t_env *)mini->env);
	if (mini->tokens)
		free_tokens(mini->tokens);
	if (mini->exec)
		free_exec(mini->exec);
	free(mini);
}
