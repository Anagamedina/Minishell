/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 22:45:27 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/04 10:19:54 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../includes/minishell.h"
void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		free_split_result(cmd->cmd_args);
		free(cmd);
	}
}

void	free_split_result(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free_cmd(tmp);
	}
}

void	free_paths(t_input input)
{
	int	i;

	if (input.path)
	{
		i = 0;
		while (input.path[i])
		{
			free(input.path[i]);
			i++;
		}
		free(input.path);
	}
}

void	free_input(t_input input)
{
	if (input.first_cmd != NULL)
		free_cmd_list(input.first_cmd);
	if (input.path != NULL)
		free_paths(input);
}
