#ifndef PROTOTYPE_H
#define PROTOTYPE_H

# include "macros.h"
# include "minishell.h"


typedef struct s_env t_env;

char	*read_input(void);

//env.c
t_env	*init_struct_env(void);
t_env	*get_env(char **envp);
void	print_env_list(t_env *env_list);

//	input.c


#endif