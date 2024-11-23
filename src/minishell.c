/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anamedin <anamedin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:05:47 by anamedin          #+#    #+#             */
/*   Updated: 2024/11/23 11:06:00 by anamedin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

// Función principal para procesar el input
int main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	char	*input = NULL; // Inicializar input a NULL
	t_env	*test_env;
	t_list 	*locals = NULL;

	// Inicializar lista de variables de entorno
	test_env = init_env(*env);
	if (!test_env)
	{
		printf("Error al inicializar la lista de variables de entorno.\n");
		return (EXIT_FAILURE);
	}

	// Bucle principal
	while (1)
	{
		input = read_input(); // Leer el input del usuario
		if (!input || !check_quotes_line(input)) // Validar el input
		{
			printf("Error al leer el input o las comillas no coinciden.\n");
			free(input);
			continue;
		}

		if (!locals)
			locals = (t_list *) create_local_vars_list(input);

		//if (ft_strcmp(input, "env") == 0)
			//print_env_list(test_env);
		else
			handle_input(NULL, (t_list **)test_env, &locals);

	}

	return (0);
}
