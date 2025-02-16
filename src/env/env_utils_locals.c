/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:04:39 by anamedin          #+#    #+#             */
/*   Updated: 2025/02/14 15:33:33 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * start with (a-z, A-Z) o _ (guion bajo).
 * Solo puede contener letras, números (0-9) y _.
 * No puede contener espacios ni caracteres especiales (!@#$%^&* etc.).
 * No puede comenzar con un número.
*/

int	validate_var_name(const char *line)
{
	int i;

	// if (!line || !(ft_isalpha(line[0]) || line[0] == '_'))
	if (!(ft_isalpha(line[0]) || line[0] == '_'))
	{
		// errno = EINVAL;
		// perror("bash: export");
		write(2, "bash: export: invalid variable name\n", 36);
		return (FALSE);
	}
	i = 1;
	while (line[i] != '\0' && line[i] != '=')
	{
		if (!(ft_isalnum(line[i]) || line[i] == '_'))
		{
			write(2, "bash: export: invalid variable name\n", 36);
			return (FALSE);
		}
		i ++;
	}
	return (TRUE);
}

/*
 * Debe comenzar con una letra (a-z, A-Z) o _ (guion bajo).
 * Solo puede contener letras, números (0-9) y _.
 * No puede contener espacios ni caracteres especiales (!@#$%^&* etc.).
 * No puede comenzar con un número.
*/

int	validate_var_value(const char *line)
{
	int	i;

	if (!line)
	{
		perror("bash: export: NULL value");
		return (FALSE);
	}
	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i ++;
	if (line[i] == '\0')
		return (TRUE);
	i ++;
	while (line[i] != '\0')
	{
		if (!(ft_isascii(line[i])))
		{
			write(2, "bash: export: invalid character in value\n", 42);
			return (FALSE);
		}
		i ++;
	}
	return (TRUE);
}

/*
 * Obtiene el nombre de la variable a partir de una línea en formato NOMBRE=VALOR.
 * Retorna una nueva cadena con el nombre de la variable.
 * Si ocurre un error de memoria, retorna NULL.
 */
char	*get_var_name(const char *line)
{
	int		i;
	int		len;
	char	*var_name;

	if (!line || line[0] == '=' || line[0] == '\0')
	{
		// errno = EINVAL;
		perror("bash: export");
		return (NULL);
	}
	i = 0;
	while (line[i] != '\0' && line[i] != '=')
		i ++;
	len = i;
	if (len == 0)
	{
		// errno = EINVAL;
		perror("bash: export");
		return (NULL);
	}
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
	{
		perror("bash: export");
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		var_name[i] = line[i];
		i ++;
	}
	var_name[i] = '\0';
	return (var_name);
}

/*
 * Obtiene el valor de la variable a partir de una línea en formato NOMBRE=VALOR.
 * Retorna una nueva cadena con el valor de la variable.
 * Si ocurre un error de memoria, retorna NULL.
 */
char	*get_var_value(char* line)
{
	int		i;
	int		j;
	int		len;
	char	*var_value;

	if (!line)
	{
		// errno = EINVAL;
		perror("bash: export");
		return (NULL);
	}
	len = (int) ft_strlen(line);
	i = len - 1;
	while (i >= 0 && line[i] != '=')
		i --;
	if (i < 0)
		return (ft_strdup(""));
	var_value = malloc(sizeof(char) * (len - i));
	if (!var_value)
	{
		perror("bash: export");
		return (NULL);
	}
	i ++;
	j = 0;
	while (i < len)
	{
		var_value[j++] = line[i++];
	}
	var_value[j] = '\0';
	return (var_value);
}

//	before was get_env_var();
char	*get_variable_in_env_list(t_list *env_list, char *key_to_find)
{
	t_list	*curr_node;
	t_env	*curr_env;

	if (!key_to_find || !env_list)
		return (NULL);
	curr_node = env_list;
	while (curr_node)
	{
		curr_env = (t_env *) curr_node->content;
		if (ft_strcmp(key_to_find, curr_env->key) == 0)
			return (curr_env->value);
		curr_node = curr_node->next;
	}
	return (NULL);
}