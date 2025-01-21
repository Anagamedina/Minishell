#include "../../includes/minishell.h"



/*t_pipe *create_pipe(int is_last)
{
	t_pipe *pipe_info = malloc(sizeof(t_pipe));
	if (!pipe_info)
	{
		perror("malloc");
		return NULL;
	}
	if (pipe(pipe_info->pipe_fds) == -1)
	{
		perror("pipe");
		free(pipe_info);
		return NULL;
	}
	pipe_info->last_cmd = is_last;
	return (pipe_info);
}



int count_pipes(t_list *token_list)
{
	int pipe_count = 0;

	t_list *current;
	t_tokens *token;

	current = token_list;

	while (current)
	{
		token = (t_tokens *)current->content;  // Asegúrate de acceder al contenido
		if (token->type_token == PIPE)  // Utiliza el campo directamente
		{
			if (!token->prev || !token->next) {
				fprintf(stderr, "Error: pipe al inicio o al final.\n");
				return -1;
			}
			if (token->prev && ((t_tokens *)token->prev)->type_token == PIPE) {
				fprintf(stderr, "Error: pipes duplicados.\n");
				return -1;
			}
			pipe_count++;
		}
		current = current->next;
	}
	return pipe_count;
}*/




/*char **split_commands(char *input)
{
	char **result = malloc(1024 * sizeof(char *));
	if (!result) return NULL;

	char *start = input;
	int i = 0;

	while (*start) {
		char *end = strchr(start, '|'); // Encuentra el delimitador '|'

		if (end) {
			*end = '\0'; // Se termina la cadena en el delimitador '|'
		}

		result[i++] = strdup(start); // Copia el comando hasta el delimitador o el final
		if (end) {
			start = end + 1; // Avanza al siguiente comando después del delimitador
		} else {
			break; // Si no hay más pipes, salimos del bucle
		}
	}

	result[i] = NULL; // Marca el final del array de strings
	return result;
}

int validate_subcommands(char *input)
{
	char **commands = split_commands(input);

	if (!commands) {
		fprintf(stderr, "Error: No se pudo dividir la cadena.\n");
		return 0;
	}

	char **current = commands;
	while (*current) {
		if (strlen(*current) == 0) {
			fprintf(stderr, "Error: subcomando vacío encontrado.\n");
			free(commands);
			return 0;
		}
		current++;
	}

	free(commands);
	return 1;
}*/