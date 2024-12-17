/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:23:07 by dasalaza          #+#    #+#             */
/*   Updated: 2024/12/17 17:48:16 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//process_token
//		Procesa un único token, verificando si necesita expansión.
/*
int	process_token_is_word(const char *str)
{
	if (str == WORD)
		return (TRUE);
	return (FALSE);
}
*/

/*
void	exist_var_value(char *var_value)
{
	if (var_value != NULL)
	{
		free();
	}

}
*/
//Una función para manejar la expansión de variables (process_variable_expansion).

/*
char	*process_variable_expansion(char *split_word_i, t_list env_list)
{

	return ();
}
*/

//Otra para unir las palabras en un único token (rebuild_token_string).
/*
char	*rebuild_token_string(void)
{

}
*/

void	split_words_aux(char *split_word, t_list *env_list)
{
	char	*var_name;
	char	*var_value;

	if (split_word[0] == DOLLAR_SIGN)
	{
		var_name = ft_strdup(split_word + 1);
		var_value = find_env_value(env_list, var_name);
		if (var_value != NULL)
		{
			free(split_word);
			split_word = NULL;
			split_word = ft_strdup(var_value);
		}
		else	//	si no se encuentra el valor de la variable se deja vacio
		{
			free(split_word);
			split_word = ft_strdup(" ");
		}
		free(var_name);
		free(var_value);
	}
}
