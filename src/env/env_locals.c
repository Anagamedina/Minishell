#include "../../includes/minishell.h"

/*
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
	if (!(ft_isalpha(line[0])) && ft_isdigit(line[0]))
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
 * 	TODO: daruny: terminar esta funcion !!
 */

//**************MAIN FUNCTION***********/
//	hello=daruny
void	check_var_local_input(char *line)
{
	t_env	*var_local_list;
//
	if (!(validate_var_name(line)))
	{
		printf("Error validating var_name\n");
		return ;
	}
	if (!(validate_var_value(line)))
	{
		printf("Error validating var_value\n");
		return ;
	}
	var_local_list = create_local_vars_list(line);
	if (!var_local_list)
	{
		printf("Error creating local variable list\n");
		free_env_list(var_local_list);
		return ;
	}
	else
	{
		printf("var_key: %s\n", var_local_list->key);
		printf("var_value: %s\n", var_local_list->value);
	}
}
