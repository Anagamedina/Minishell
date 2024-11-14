/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:19 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/07 13:48:39 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_input(void)
{
	char *input;

	input = readline("minishell> "); // Muestra el prompt y lee la entrada
	if (input && *input)
	{
		add_history(input);
		//printf("line: %s\n", input);
	}
	return (input);
}

/*
 * comprobar que si se encuentra el caracter "
 * ha de encontrar otro que es el que cierra "
 * "hello!"
 * Verificar si empieza y termina con comillas dobles
*/
int	check_quotes_line(char *line)
{
	int i;
	int double_quotes;
	int single_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"')
			double_quotes++;
		else if (line[i] == '\'')
			single_quotes++;
		i++;
	}
	// Verificamos que ambos contadores de comillas sean pares
	if (double_quotes % 2 != 0)
		return (0);
	if (single_quotes % 2 != 0)
	{
		printf("Error: Unmatched single quotes in the input.\n");
		return (2);
	}
	return (1);
}

/*
 * TODO daruny: terminar esta funcion
 * checkear el orden la linea: comando option argumento
 * echo -n abcd
*/

//	NOMBRE=VALOR
int	validate_var_name(const char *line)
{
	int i;

	i = 0;
	//	verificar primer caracter si es a-zA-z o '_'
	if (!(ft_isalpha(line[i])) || line[i] == '_')
		return (0);
	i++;
	while (line[i] != '\0' && line[i] != '=')
	{
		if (!(ft_isalnum(line[i])))
			return (0);
		i ++;
	}
	if (line[i] == '=')
		return (1);
	return (0);
}

//	NOMBRE=VALOR
int	validate_var_value(const char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0' || line[i] != '=')
		i ++;
	if (line[i] != '=')
		return (0);
	i ++;
	while (line[i] != '\0')
	{
		if (!(ft_isalnum(line[i])))	//	?
			return (0);
		i ++;
	}
	return (1);
}

char	*get_var_name(char *line)
{
	int		i;
	int		len;
	char	*var_name;

	i = 0;
	while (line[i] != '\0' && line[i] != '=')
		i ++;
	len = i;
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (i < len)
	{
		var_name[i] = line[i];
		i ++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*get_var_value(char *line)
{
	int		i;
	int		j;
	int		len;
	char	*var_value;

	len = ft_strlen(line);
	i = len - 1;
	while (i >= 0 && line[i] != '=')
		i --;
	var_value = malloc(sizeof(char) * (len - i + 1));
	if (!var_value)
		return (NULL);
	i = i + 1;
	j = 0;
	while (i < len)
	{
		var_value[j] = line[i];
		i ++;
		j ++;
	}
	var_value[i] = '\0';
	return (var_value);
}

/*
 * gestionar variables locales(crear una lista)
 * siguiendo el patron el el prompt:
 * 	"MY_VAR=hello world!";		//valido
 * 	"1INVALID=hello";		//invalido
 * 	"VALID_VAR=";		//valido(valor vacio es permitico)

 * hay que guardarlo en una struct separado de env
 * Example:
 * case01:
 * 		daruny=123
 * 		echo $daruny -> 123
 * case02:
 * 		daruny="1"
 * 		echo $daruny -> 1
 * case03:
 * 		d='1'
 * 		echo $d -> 1
 * 	TODO: daruny: terminar esta funcion de get_local_variables_list
 */
t_env	*create_local_vars_list(char *line)
{
	t_env	*local_variable;
	int 	i;

	i = 0;
	while (line[i] != '\0')
	{
		local_variable = init_struct_env();
		if (local_variable == NULL)
			return (NULL);
//		local_variable->full_var = ft_strdup(line);
		local_variable->key = get_var_name(line);
		local_variable->value = get_var_value(line);
		local_variable->next = NULL;
	}
	return (local_variable);
}

//	hello=daruny
void	validate_input(char *line)
{
	if (check_quotes_line(line) == 0)
		printf("Error: Unmatched double quotes in the input.\n");
	if (validate_var_name(line) == 0 || validate_var_value(line) == 0)
		printf("Error validating var_name and var_value\n");
	else
	{

	}
/*	if (line is correct)
	{
 		get_var_name
 		get_var_value
		add to new lista enlazada de variables locales
	}
*/
}
