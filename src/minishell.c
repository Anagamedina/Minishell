
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
	//Parsear el input
	if (check_syntax(input))
	{
		

	}
	return 0;
}
