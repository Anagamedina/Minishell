/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:34:31 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/07 13:35:45 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
typedef struct s_env
{
	char            *key;            // Clave de la variable de entorno
	char            *value;          // Valor de la variable de entorno
	char            *full_var;       // Cadena completa "key=value" (opcional) ??
	struct s_env    *next;           // Puntero al siguiente nodo
}                   t_env;
*/

t_env	*init_struct_env(void)
{
	t_env	*new_envp;

	new_envp = (t_env *)malloc(sizeof(t_env));
	if (!new_envp)
		return (NULL);
	new_envp->value = NULL;
	new_envp->key = NULL;
	new_envp->full_var = NULL;
	new_envp->next = NULL;
	return (new_envp);
}
