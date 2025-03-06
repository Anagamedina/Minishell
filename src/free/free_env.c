/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/03/06 17:57:16 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 21:45:06 by dasalaza          #+#    #+#             */
/*   Updated: 2025/01/31 18:10:16 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_void(void *content)
{
	t_env	*env;

	if (!content)
		return ;
	env = (t_env *)content;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	// if (env->full_var)
		// free(env->full_var);

	free(env);
}

void	free_env_list(t_list **env)
{
	if (!env || !*env)
		return ;
	ft_lstclear(env, (void (*)(void *))free_env_void);
	*env = NULL;
}
void	free_env_node(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	// if (env->full_var)
		// free(env->full_var);
	free(env);
}
