//
// Created by daruuu on 11/2/24.
//
#include "../includes/minishell.h"

// main para la lectura de la terminal del user.
// int	main(int argc, char **argv, char **env)
// {
// 	if (argc == 1)
// 	{
// 		printf("error\n");
// 	}

// 	return (0);
// }
int	main(int argc, char **argv, char **env)
{
	t_input	input;

	if(argc == 1)
	{
		perror("Error: ./input infile cmd1 cmd2 outfile");
		return (EXIT_FAILURE);
	}
	else
	{
		input = init_input(argc, argv, env);
		print_input(&input);

		// while(1)
		// {
		// 	if (!input.first_cmd)
		// 	{
		// 		free_input(input);
		// 		return (EXIT_FAILURE);
		// 	}
		// 	// handle_commands(&input);
		// 	// print_paths(input.path);
		// 	// print_input(&input);
		// }
        // free_input(input);
	}
	return (0);
}
