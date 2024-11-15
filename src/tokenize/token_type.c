/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:20 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/12 13:30:21 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char*)s1 - *(unsigned char *)s2);
}

//	(*tokens)->str
int	set_token_type(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (REDIR_INPUT);
	else if (ft_strcmp(str, ">") == 0)
		return (REDIR_OUTPUT);
	else if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(str, ">>") == 0)
		return (CONCAT_OUTPUT);
	else if (str && ft_strlen(str) >= 0)
		return (WORD);
	else
		return (NULL_TYPE);	//error en seleccionar!!!
}



//  ls -l | cat -w | < **
/*int	identify_redirecctions_pipes(char *readline)
{
	int words_in_line;
	char **clean_line;

	words_in_line = count_words(readline);
	if (words_in_line > 0) {
		clean_line = ft_split(readline, ' ');
		//  categorizar cada token con su tipo

	}
}*/

