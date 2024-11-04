//
// Created by daruuu on 11/2/24.
//

#ifndef PARSING_H
# define PARSING_H


typedef struct s_cmd
{
	// "wc -l" sería el comando y sus parámetros:
	// cmd_args[0] = "wc"
	// cmd_args[1] = "-l"
	char			**cmd_args;
	int				cmd_id;
	// int				pipe[2];
	int				input_fd;
	int				output_fd;
	struct s_cmd	*next;
}				t_cmd;

//estructura para guardar el input
typedef struct s_input
{
	t_cmd			*first_cmd;
	char			**path;
	int				cmd_count;
	char			**argvs;
	char			**env;
	int				input_fd;
	int				output_fd;
}				t_input;


//	GET_INPUT.C
//	Commands and command lists
t_cmd			*cmd_new(char *str, char **paths);
t_cmd			*create_cmd_list(t_input *pipex);
int				open_files(t_input *input, char **argv, int argc);
t_input			init_input(int argc, char **argv, char **env);


//	PATHS.C
// Path and command management
char		*get_cmd_path(char *cmd, char **paths);
t_cmd		*handle_cmd_error(t_cmd *new);
char		**get_path(char **env);

// Memory release functions
void			free_cmd(t_cmd *cmd);
void			free_cmd_list(t_cmd *cmd_list);
void			free_paths(t_input pipex);
void			free_input(t_input input);
void			free_pipex(t_input pipex);
void			free_split_result(char **result);


// tests
void print_input(t_input *input);
void print_paths(char **paths);
#endif
