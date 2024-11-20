/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:54:28 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/20 11:54:33 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//*tokens[0] es export (el nombre del builtin),
//tokens[1] es PATH=/usr/local/bin,
// PATH=/usr/local/bin y HOME=/home/user.
// Estos se consideran los argumentos para el comando export*/

//*Los tokens que siguen a export (tokens[1], tokens[2], ...)
// representan las variables de entorno que deseas añadir o modificar.*/

/*
 * find key iterating througth list
 * and change env->value;
 *	crear una nueva VARIABLE de entorno a nuestro ENV
 *	call init_struct_env()
 *	ft_lst_add_back()
 */

t_env	*add_new_var(t_env **list_envp, char *cmd)
{
	char	**tokens;
	t_env	*new_var;

	tokens = ft_split(cmd, '=');
	if (tokens && tokens[0] && tokens[1])
	{
		//verificar que exista esa varible de entorno en env
		new_var = ft_lstnew(tokens[0]);
		ft_lstadd_back(list_envp, new_var);
	}
	else if (tokens && tokens[0])
	{
		//mirar si existe la key dentro de env
		new_var = ft_lstnew("")

	}


}



/*
void	modify_var_env(t_env **list_envp, char *key)
{

}
*/


