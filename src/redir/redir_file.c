#include "../../includes/minishell.h"


//funcion que abra el archivo dependiendo del tipo de redireccion
//devuleve un fd del archivo abierto
int open_file(char *file,int type)
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

//funcion que se encarga de duplicar el descriptorde archivo en el
// descriptor de entrada o salida corespodiente
//cmd --> tiene sus fd de entrada y salida
//y cuando abrimos un arhivo no es el mismo fd del comando
//por eso lo redirigimos
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

//
void 	handle_redirection(char *file, t_cmd *cmd, int type)
{
	int fd;
	int target_fd;

	if (type == REDIR_IN) // <
		target_fd = cmd->input_fd;
	else if (type == REDIR_OUT) //>
		target_fd = cmd->output_fd;
	else
		return ;
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


// Es útil cuando el archivo de entrada puede no existir
// y en su lugar se quiere crear un pipe vacío para seguir con la ejecución del pipeline

int input_redirect_with_default(char *file, t_cmd *cmd)
{
	int fd;
	int pfd[2];

	// Intentar abrir el archivo en modo lectura
	fd = open(file, O_RDONLY);
	if (fd == -1) { // Si no se puede abrir el archivo, creamos un pipe vacío
		// Crear un pipe vacío
		if (pipe(pfd) == -1) {
			perror("Error creating pipe");
			exit(1);
		}

		// Redirigir la entrada al pipe vacío
		if (dup2(pfd[0], cmd->input_fd) == -1) {
			perror("Error duplicating pipe");
			exit(1);
		}

		// Cerrar el pipe ya que no se usará más
		close(pfd[0]);
		close(pfd[1]);

		free(file);  // Liberar el nombre del archivo
		return 1;    // Continuar la ejecución con un flujo vacío
	}

	// Si el archivo existe, redirigir normalmente
	if (dup2(fd, cmd->input_fd) == -1) {
		perror("Error dup");
		exit(1);
	}
	close(fd); // Cerrar el archivo
	free(file);  // Liberar el nombre del archivo
	return 0;    // Redirección exitosa
}
