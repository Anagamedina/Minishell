/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:29:30 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/12 13:29:40 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/* parametros : especificar el tipo del token que se está creando*/

t_tokens	*init_token(char *str, t_token_type token_type)
{
	t_tokens	*new_token;

	new_token = malloc(sizeof(t_tokens));
	if(!new_token)
		return (NULL);
	new_token->str = ft_strdup(str);
	new_token->token_type = token_type;
	new_token->length = ft_strlen(str);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}