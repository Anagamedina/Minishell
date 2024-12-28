#include "../../includes/minishell.h"


//Gestionar redrrecciones de entrada (<)
//si el archivo no existe simula un flujo vacio usando una pipe 
//si el archivo existe redirige su contenido como entrada estandar para el f
/*void 	get_files(char *file, t_cmd *cmd, int type)
{
	int fd;

	if (type == REDIR_IN || type == REDIR_ERR_OUT)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else 
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	 if (fd == -1)
	 	printf("error fd");
	if (type == REDIR_ERR_APPEND || type == REDIR_ERR_OUT)
	{
		if (dup2(fd, ))
	}

}*/

/*int	handle_input_redirection(char *file, t_cmd *cmd)
{
	int	fd;
	int	pfd[2];

	// Intentar abrir el archivo
	fd = open(file, O_RDONLY);
	if (fd == -1) // Si el archivo no existe
	{
		// Crear un pipe vacío (pipe imaginario)
		if (pipe(pfd) == -1)
			exit_error("Error creating pipe", 50);

		// Redirigir la entrada al pipe vacío
		if (dup2(pfd[0], cmd->pipes->in) == -1)
			exit_error("Error duplicating pipe", 51);

		// Cerrar el pipe ya que no se usará más
		close(pfd[0]);
		close(pfd[1]);
		free(file);
		return (1); // El flujo sigue adelante
	}

	// Si el archivo existe, redirigir normalmente
	if (dup2(fd, cmd->pipes->in) == -1)
		exit_error("Error dup", 45);
	close(fd);
	free(file);
	return (0);
}*/