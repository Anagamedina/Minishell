/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:58 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/25 10:47:53 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static void	check_file(t_tokens *curr_token, t_tokens *curr_next)
{
	int	fd;

	// Si curr_next no es un nombre de archivo, solo crear un archivo vacío
	if (!curr_next || curr_next->type_token != FILENAME)
	{
		printf("DEBUG: Creando archivo vacío '%s'\n", curr_token->str);
		fd = open_file(curr_token->str, REDIR_OUT);
		if (fd == -1)
			perror("Error creando archivo vacío");
		else
			close(fd);
		return;
	}

	// Caso normal: abrir archivo con el nombre dado
	fd = open_file(curr_next->str, REDIR_OUT);
	if (fd == -1)
		perror("Error abriendo archivo de SALIDA");
	else
		close(fd);
}



void	parse_redir(t_mini *mini)
{
	t_list		*token_list;
	t_tokens	*curr_token;
	t_tokens	*curr_token_next;

	token_list = mini->tokens;
	while (token_list != NULL)
	{
		curr_token = (t_tokens *)token_list->content;

		if (token_list->next != NULL)
		{
			curr_token_next = (t_tokens *)token_list->next->content;

			if (is_redir(curr_token) == TRUE && curr_token_next->type_token == FILENAME )
				check_file(curr_token, curr_token_next);
		}

		token_list = token_list->next;
	}
}