/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:30:30 by anamedin          #+#    #+#             */
/*   Updated: 2024/12/03 13:55:15 by  dasalaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *ft_strncpy(char *s1, char *s2, int n)
{
	int i = 0;
	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
/*
 * Esta función se encarga de saltar entre comillas simples o dobles.
 *
 * Desde una posicion especifica cuando se encuenta las QUOTES
 * me vas a recorrer la i(puntero) hasta hacer match con la quote
 * Retorna 1 para indicar que se encontró una palabra
 * */
static int skip_quotes(char *str, int *i)
{
	char quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
	return (1);
}

/*Cuenta cuántas "palabras" hay en la cadena str,
 * tomando en cuenta las comillas
 */
static int	count_words(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i] == '\'' || str[i] == '"')
			wc += skip_quotes(str, &i);
		else if (str[i] == ';')
		{
			wc++; // Contar `;` como una palabra/token
			i++;  // Avanzar al siguiente carácter
		}
		else if (str[i])
		{
			wc++;
			while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != ';'))
				i++;
		}
	}
	return (wc);
}

/*
Esta función salta los espacios,
tabulaciones y saltos de línea.
 */
static void skip_whitespace(char *str, int *i)
{
	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\n'))
		(*i)++;
}


/*Se encarga de copiar una palabra (definida entre espacios,
 * tabulaciones o comillas) en la posición de la lista out*/
static int copy_word(char **out, char *str, int start, int end, int *k)
{

	//TODO eleminar parametros ANA
	out[*k] = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!out[*k])
		return (-1);
	ft_strncpy(out[(*k)++], &str[start], end - start);
	return (0);
}

/*Inicializa las variables necesarias antes de
 * comenzar el procesamiento de la cadena*/
static int	init_vars_split(int *i, int *k, int *wc, char ***out, char *str)
{
	//TODO eleminar parametros ANA
	*i = 0;
	*k = 0;
	*wc = count_words(str);
	*out = (char **)malloc(sizeof(char *) * (*wc + 1));
	if (!*out)
		return (-1);
	return (0);
}


/*Es la función principal que utiliza
las otras funciones para dividir la cadena
 en palabras, considerando las comillas.
*/
//**********MAIN FUNCTION***************/
char **ft_split_quote(char *str)
{
	int i;
	int j;
	int k;
	int wc;
	char **out;

	if (init_vars_split(&i, &k, &wc, &out, str) == -1)
		return (NULL);

	while (str[i])
	{
		skip_whitespace(str, &i);
		j = i;
		// si es comilla simple o comilla doble
		if (str[i] == '\'' || str[i] == '"')
			skip_quotes(str, &i);
		else if (str[i] == ';')
			i++;
		else
		{
			while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != ';'))
				i++;
		}
		if (i > j && copy_word(out, str, j, i, &k) == -1)
			return (NULL);
	}
	out[k] = NULL;
	return (out);
}
