

#include "../../includes/minishell.h"
/* Función que maneja la ejecución de los comandos builtins
static void execute_builtin(t_cmd *cmd, t_mini *mini)
{
	if (strcmp(cmd->cmd, "echo") == 0)
		ft_echo(cmd);
	else if (strcmp(cmd->cmd, "cd") == 0)
		ft_cd(cmd, mini);
	else if (strcmp(cmd->cmd, "pwd") == 0)
		ft_pwd();
	else if (strcmp(cmd->cmd, "export") == 0)
		ft_export(cmd, mini);
	else if (strcmp(cmd->cmd, "unset") == 0)
		ft_unset(cmd, mini);
	else if (strcmp(cmd->cmd, "env") == 0)
		ft_env(mini);
	else if (strcmp(cmd->cmd, "exit") == 0)
		ft_exit(cmd);
}*/


/*char **lst_to_arr(t_list *lst, char **envp)
{
	t_list *current = lst;
	int count = 0;
	char **arr;

	if (!lst)
	{
		while (envp[count])
			count++;

		arr = ft_calloc( count + 1, sizeof(char *));
		if (!arr)
			return NULL;

		current = lst;
		while (envp[count])
		{
			arr[count] = ft_strdup(envp[count]); // Copiar la cadena
			count++;
		}

		arr[count] = NULL;  // Terminamos el array con NULL
		return arr;
	}

	// Si tenemos una lista enlazada, contamos los elementos de la lista
	current = lst;
	while (current)
	{
		count++;
		current = current->next;
	}

	// Reservamos memoria para el array de cadenas
	arr = ft_calloc( count + 1, sizeof(char *)); // +1 para el NULL final
	if (!arr)
		return NULL;

	// Copiamos las cadenas de la lista enlazada al array
	current = lst;
	count = 0;
	while (current)
	{
		arr[count] = ft_strdup(((t_env *)current->content)->full_var); // Copiar la cadena de cada nodo
		current = current->next;
		count++;
	}

	arr[count] = NULL;

	return arr;
}
*/

// OPEN INPUT FILE
//int	open_files(t_input *input, char **argv, int argc)
//{
//	input->input_fd = open(argv[1], O_RDONLY);
//	if (input->input_fd == -1)
//	{
//		perror("Error: Cannot open INPUT file");
//		return (0);
//	}
//	input->output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//	if (input->output_fd == -1)
//	{
//		perror("Error: Cannot open OUTPUT file");
//		close(input->input_fd);
//		return (0);
//	}
//	return (1);
//}
//
// INIT STRUCT
