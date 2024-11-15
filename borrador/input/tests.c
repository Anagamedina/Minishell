
#include "../../includes/minishell.h"


void print_paths(char **paths)
{
	int i = 0;
	if(paths == NULL)
	{
		printf("NO paths found. \n");
		return;
	}
	while(paths[i])
	{
		printf("path[%d]: %s\n", i, paths[i]);
		i++;
	}
}


// Función para imprimir la estructura t_input
void print_input(t_input *input)
{
    t_cmd *current_cmd = input->first_cmd; // Iniciar en el primer comando
    // Imprimir información básica de t_input
    printf("input Structure:\n");
    printf("Command Count: %d\n", input->cmd_count);
    printf("Input File Descriptor: %d\n", input->input_fd);
    printf("Output File Descriptor: %d\n", input->output_fd);
    
    // Imprimir las rutas disponibles
    printf("Paths:\n");
    int i = 0;
    while (input->path[i] != NULL)
    {
        printf("path[%d]: %s\n", i, input->path[i]);
        i++;
    }
    
    // Imprimir los comandos en la lista
    printf("Commands:\n");
    while (current_cmd != NULL)
    {
        printf("  Command Number: %d\n", current_cmd->cmd_id);
        printf("  Arguments:\n");
        
        int j = 0;
        while (current_cmd->cmd_args[j] != NULL)
        {
            printf("    arg[%d]: %s\n", j, current_cmd->cmd_args[j]);
            j++;
        }
        // Imprimir los descriptores de archivo del pipe
        // printf("  Pipe FD: [%d, %d]\n", current_cmd->pipe[0], current_cmd->pipe[1]);
        
        // Avanzar al siguiente comando
        current_cmd = current_cmd->next;
    }
}
