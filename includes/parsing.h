//
// Created by daruuu on 11/2/24.
//

#ifndef PARSING_H
#define PARSING_H

//estructura para guardar el input
typedef struct s_input
{
	char	**argvs;
	char	**env;
	char	**path;
	int		cmd_count;
};

#endif
