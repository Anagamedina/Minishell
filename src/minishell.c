
#include "../includes/minishell.h"

int main(void)
{
	char	*input;

	while (1)
	{
		input = read_input();
		if (!input)
		{
			// printf(stderr, "Error al leer el input\n");
			printf("Error al leer el input\n");
			continue;
		}
	}
	// 2. Parsear el input
	// if (check_syntax(input))
	// {
	// 	// Aquí deberías crear y manejar la lista de comandos
	// 	// Suponiendo lista_comandos es un arreglo de cadenas

	// }
	return 0;
}
