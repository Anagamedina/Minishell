
#include "../../includes/minishell.h"

// Función para liberar la memoria de las palabras y el array de punteros

void	free_split_result(char **out)
{
	int	i;

	i = 0;
	while (out[i] != NULL)
	{
		free(out[i]);
		i++;
	}
	free(out);
}
