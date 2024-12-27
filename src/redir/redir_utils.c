#include "../../includes/minishell.h"


//Gestionar redrrecciones de entrada (<)
//si el archivo no existe simula un flujo vacio usando una pipe 
//si el archivo existe redirige su contenido como entrada estandar para el f
void 	get_files(char *file, t_cmd *cmd, int type)
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

}