

#include "../../includes/minishell.h"


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
