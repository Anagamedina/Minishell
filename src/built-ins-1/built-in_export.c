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
/*modify_var_env()
    |
    v
get_var_name(line)    -> Obtén el nombre de la variable (key)
    |
    v
get_var_value(line)   -> Obtén el valor de la variable (value)
    |
    v
find_env_var(*env_list, key)   -> ¿La variable ya existe en la lista?
    |
    |---> Si existe: actualizarla
    |       |
    |       v
    |   free(existing_var->value)       -> Libera el valor antiguo
    |   existing_var->value = strdup(value)  -> Asigna el nuevo valor
    |   free(existing_var->full_var)      -> Libera la cadena completa anterior
    |   existing_var->full_var = strdup(line) -> Asigna la nueva cadena
    |
    |---> Si no existe: crear nueva
            |
            v
create_env_node(line) -> Crear un nuevo nodo
            |
            v
add_env_back(*env_list, new_node) -> Añadir el nuevo nodo al final de la lista
*/





/*
 * Función que busca una variable de entorno en la lista.
 * Si la encuentra, retorna el nodo correspondiente; si no, retorna NULL.
 */
 t_env	*find_env_var (t_env *env_list, char *key)
 {
	 while (env_list != NULL)
	 {
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list);
		env_list = env_list->next;
	}
	 return (NULL);
}


/*
 * Función que crea un nuevo nodo para una variable de entorno a partir de la línea
 * proporcionada (por ejemplo, "PATH=/usr/local/bin").
 * Retorna un puntero al nodo creado o NULL si ocurre un error.
 */
t_env	*create_env_node(char *line)
{
	 t_env	*node = init_env_list();
	 if (!node)
		 return (NULL);
	 node->full_var = ft_strdup(line);
	 node->key = get_var_name(line);
	 node->value = get_var_value(line);
	 return (node);
}


/*
 * Función que agrega un nuevo nodo al final de la lista de variables de entorno.
 */
void	add_env_back(t_env **env_list, t_env *new_node)
{
	 t_env	*current;

	 if(!env_list || !new_node)
		 return ;

	 current = *env_list;
	 while (current->next != NULL)
		 current = current->next;
	current->next = new_node;
}

/*
 * Función que modifica una variable de entorno en la lista de entornos.
 * Si la variable ya existe, se actualiza su valor; si no, se agrega una nueva variable
 * al final de la lista.
 */

void	modify_var_env(t_env **env_list, char *line)
{
	 char *key;
	 char *value;
	 t_env *existing_var;

	 key = get_var_name(line);
	 value = get_var_value(line);
	 existing_var = find_env_var(*env_list);

	 if (existing_var)
	 {
		 free(existing_var->value);
		 existing_var->value = ft_strdup(value);
		 free(existing_var->full_var);
		 existing_var->full_var = ft_strdup(line);
	 }
	 else
	 {
		 t_env *new_node = create_env_node(line);
		 if (new_node)
			 add_env_back((env_list, new_node));
	 }

}



//**********BORRAR************/
//*tokens[0] es export (el nombre del builtin),
//tokens[1] es PATH=/usr/local/bin,
// PATH=/usr/local/bin y HOME=/home/user.
// Estos se consideran los argumentos para el comando export*/

//*Los tokens que siguen a export (tokens[1], tokens[2], ...)
// representan las variables de entorno que deseas añadir o modificar.*/


/*
 * static int	just_export(t_env *env)
{
	while (env != NULL)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->val);
		env = env->next;
	}
	return (0);
}