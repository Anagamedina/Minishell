
#include "../../includes/minishell.h"
//  CREAR NODOS DE CADA COMANDO
//str  =  "ls -l"
// new->cmd_args[0]  = "ls",
// new->cmd_args[1]  = "-l".
t_cmd	*cmd_new(char *str, char **paths)
{
	t_cmd	*new;
	char	*cmd_path;

	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		perror("Error: malloc failed");
		return (NULL);
	}
	new->cmd_args = ft_split(str, ' ');
	if (!new->cmd_args)
	{
		perror("Error: ft_split failed");
		return (NULL);
	}
	cmd_path = get_cmd_path(new->cmd_args[0], paths);
	if (cmd_path == NULL)
		return (handle_cmd_error(new));

	free(new->cmd_args[0]);
	new->cmd_args[0] = cmd_path;
	new->next = NULL;
	return (new);
}

//  CREAR LA LISTA DE CADA COMANDO
t_cmd	*create_cmd_list(t_input *input)
{
	t_cmd	*first;
	t_cmd	*cmd;
	t_cmd	*new;
	int		i;

	i = 0;
//	while (input->argvs[i])
//	{
//		printf("%s\n", input->argvs[i]);
//		i ++;
//	}
	first = cmd_new(input->argvs[2], input->path);
	if (!first)
		return (NULL);
	first->cmd_id = 2;
	cmd = first;
	i = 0;
	while (i < input->cmd_count - 1)
	{
		new = cmd_new(input->argvs[3 + i], input->path);
		if (!new)
		{
			free_cmd_list(first);
			return (NULL);
		}
		new->cmd_id = i + 3;
		cmd->next = new;
		cmd = new;
		i++;
	}
	return (first);
}

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
//TODO
t_input	init_input(int argc, char **argv, char **env)
{
	t_input	input;

	input.cmd_count = (argc - 1);
	// printf("%d\n", input.cmd_count);
	input.argvs = argv;
	// input.input_fd = open(argv[1], O_RDONLY);
	input.env = env;
	// if (!open_files(&input, argv, argc))
	// 	exit(EXIT_FAILURE);
	input.path = get_path(env);
	if (!input.path)
	{
		perror("Error: No se pudo obtener las rutas");
		exit(EXIT_FAILURE);
	}

	input.first_cmd = create_cmd_list(&input);
	if (input.first_cmd == NULL)
	{
		free_cmd_list(input.first_cmd);
		free_paths(input);
		exit(EXIT_FAILURE);
	}
	return (input);
}
