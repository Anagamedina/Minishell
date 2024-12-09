/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:04:39 by anamedin          #+#    #+#             */
/*   Updated: 2024/12/03 16:48:54 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

/*
ana=
 * Valida si el nombre de una variable es correcto.
 * Un nombre válido comienza con una letra o un guion bajo ('_')
 * y solo puede contener caracteres alfanuméricos.
 * Retorna 1 si es válido, 0 si no lo es.
*/
int	validate_var_name(const char *line)
{
	int i;

	// Verificar primer carácter si es a-zA-Z o '_'
	// agregar caso de '_' da error !!!
	if (!(ft_isalpha(line[0])) || ft_isdigit(line[0]))
		return (FALSE);	//0
	i = 1;
	while (line[i] != '\0' && line[i] != '=')
	{
		if (!(ft_isalnum(line[i]) || line[i] == '_'))
			return (FALSE);
		i++;
	}
	if (line[i] == '=')
		return (TRUE);
	else
		return (FALSE);
}

/*
 * Valida si el valor de una variable es correcto.
 * Un valor válido está después del carácter '=' y
 * solo contiene caracteres alfanuméricos.
 * Retorna 1 si es válido, 0 si no lo es.
 */
int	validate_var_value(const char *line)
{
	int i;

	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i++;
	if (line[i] != '=')
		return (FALSE);
	i++;
	while (line[i] != '\0')
	{
		if (!(ft_isascii(line[i])))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
 * Obtiene el nombre de la variable a partir de una línea en formato NOMBRE=VALOR.
 * Retorna una nueva cadena con el nombre de la variable.
 * Si ocurre un error de memoria, retorna NULL.
 */
char	*get_var_name(char *line)
{
	int		i;
	int		len;
	char	*var_name;

	i = 0;
	while (line[i] != '\0' && line[i] != '=')
		i++;
	len = i;
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		var_name[i] = line[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}



/*
 * Obtiene el valor de la variable a partir de una línea en formato NOMBRE=VALOR.
 * Retorna una nueva cadena con el valor de la variable.
 * Si ocurre un error de memoria, retorna NULL.
 */
char	*get_var_value(char *line)
{
	int		i;
	int		j;
	int		len;
	char	*var_value;

	len = ft_strlen(line);
	i = len - 1;
	while (i >= 0 && line[i] != '=')
		i--;
	var_value = malloc(sizeof(char) * (len - i + 1));
	if (!var_value)
		return (NULL);
	i = i + 1;
	j = 0;
	while (i < len)
	{
		var_value[j] = line[i];
		i++;
		j++;
	}
	var_value[j] = '\0'; // Corrige el índice aquí para terminar correctamente la cadena
	return (var_value);
}



