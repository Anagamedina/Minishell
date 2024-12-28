#include "../../includes/minishell.h"

// Abre un archivo según el tipo de redirección especificado
// type puede ser REDIR_IN (<), REDIR_OUT (>), o REDIR_APPEND (>>)
// Retorna el descriptor de archivo (fd) abierto o -1 si ocurre un error
int open_file(char *file, int type)
{
	int fd;

	if (type == REDIR_IN)
		fd = open(file, O_RDONLY);
	else if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (-1);
	return (fd);
}

// Duplica un descriptor de archivo al descriptor de entrada o salida correspondiente
// Luego cierra el descriptor original para evitar fugas de recursos
void redirect_file(int fd, int target_fd)
{
	if (dup2(fd, target_fd) == -1)
	{
		perror("Error duplicando descriptor");
		exit(1);
	}
	if (close(fd) == -1)
	{
		perror("Error cerrando descriptor");
		exit(1);
	}
}

// Maneja la redirección de entrada con un valor predeterminado
// Si el archivo de entrada no existe, crea un pipe vacío para continuar la ejecución
// Devuelve 0 si la redirección es exitosa y 1 si se usa un flujo vacío
int input_redirect_with_default(char *file, t_cmd *cmd)
{
	int fd;
	int pfd[2];

	// Intentar abrir el archivo en modo lectura
	fd = open(file, O_RDONLY);
	if (fd == -1) {
		if (pipe(pfd) == -1) {
			perror("Error creating pipe");
			exit(1);
		}

		// Redirigir la entrada al pipe vacío
		if (dup2(pfd[0], cmd->input_fd) == -1) {
			perror("Error duplicating pipe");
			exit(1);
		}

		close(pfd[0]);
		close(pfd[1]);

		free(file);
		return 1;    // Continuar la ejecución con un flujo vacío
	}

	// Si el archivo existe, redirigir normalmente
	if (dup2(fd, cmd->input_fd) == -1)
	{
		perror("Error dup");
		exit(1);
	}
	close(fd);
	free(file);
	return 0;
}

// Maneja la redirección de entrada o salida de un comando
// Abre el archivo correspondiente, redirige el descriptor de archivo y lo cierra
void handle_redirection(char *file, t_cmd *cmd, int type)
{
	int fd;
	int target_fd;

	if (type == REDIR_IN) // <
		target_fd = cmd->input_fd;
	else if (type == REDIR_OUT) // >
		target_fd = cmd->output_fd;
	else
		return;

	fd = open_file(file, type);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	redirect_file(fd, target_fd);
	if (close(fd) == -1)
	{
		perror("Error closing file");
		exit(1);
	}
	free(file);
}