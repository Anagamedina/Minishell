# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 17:34:21 by anamedin          #+#    #+#              #
#    Updated: 2024/12/03 16:55:21 by anamedin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes  -I$(LIBFT_DIR) #-fsanitize=address

SRC_DIR = src
SRC_ENV= $(SRC_DIR)/env
SRC_MINI= $(SRC_DIR)/mini
SRC_INPUT= $(SRC_DIR)/input
SRC_PARSE= $(SRC_DIR)/parser
SRC_TOKEN = $(SRC_DIR)/tokenize
SRC_BUILTINS1 = $(SRC_DIR)/built_ins_1
SRC_BUILTINS2 = $(SRC_DIR)/built_ins_2
SRC_CMD = $(SRC_DIR)/commands
OBJ_DIR = obj
LIBFT_DIR = libft
MINISHELL_H = includes/minishell.h

SRC = 	$(SRC_DIR)/minishell.c \
		$(SRC_MINI)/init_struct.c \
		$(SRC_INPUT)/input.c \
		$(SRC_PARSE)/parser_syntax_dollar.c \
		$(SRC_PARSE)/parser_syntax_expand.c \
		$(SRC_PARSE)/parser_syntax_quotes.c \
		$(SRC_ENV)/env.c \
		$(SRC_ENV)/env_utils_locals.c \
		$(SRC_ENV)/env_locals_list.c \
		$(SRC_ENV)/free_env.c \
		$(SRC_TOKEN)/token_type.c \
		$(SRC_TOKEN)/token_utils.c \
		$(SRC_TOKEN)/token_free.c \
		$(SRC_TOKEN)/token_list.c \
		$(SRC_CMD)/init_commands.c \
		$(SRC_CMD)/errors_commands.c \
		$(SRC_BUILTINS1)/built_in_export.c \
		$(SRC_BUILTINS1)/built_in_utils.c \
		$(SRC_DIR)/built_ins_main.c \
		$(SRC_BUILTINS2)/builtin_pwd.c \
		$(SRC_BUILTINS2)/builtin_cd.c \
		$(SRC_BUILTINS2)/builtin_exit.c


OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

#OBJ = $(patsubst \
#		$(SRC_DIR)/%.c, \
#		$(SRC_INPUT)/%.c, \
#		$(SRC_ENV)/%.c, \
#		$(SRC_TOKEN)/%.o, \
#		$(OBJ_DIR)/%.o, \
#		$(SRC))
#falta los .o del bonus 

LIBFT = $(LIBFT_DIR)/libft.a

# ==================================== #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MINISHELL_H) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
#	@mkdir -p $(OBJ_DIR)

# ==================================== #
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

# ==================================== #
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
