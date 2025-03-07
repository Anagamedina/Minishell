/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exce_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:39:58 by anamedin          #+#    #+#             */
/*   Updated: 2025/03/07 18:40:07 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_memory_allocation_error(void)
{
	perror("Error: No se pudo asignar memoria en env_list_to_array");
}

void	handle_env_duplication_error(char **env_array, int index)
{
	perror("Error: No se pudo duplicar variable de entorno");
	free_env_array(env_array, index);
}
