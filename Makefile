# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 17:34:21 by anamedin          #+#    #+#              #
#    Updated: 2024/11/07 14:28:23 by anamedin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes  -I$(LIBFT_DIR) #-fsanitize=address

SRC_DIR = src
SRC_ENV= $(SRC_DIR)/env
SRC_INPUT= $(SRC_DIR)/input
SRC_TOKEN = $(SRC_DIR)/tokenize
OBJ_DIR = obj
LIBFT_DIR = libft
MINISHELL_H = includes/minishell.h

SRC = 	$(SRC_DIR)/minishell.c \
		$(SRC_INPUT)/input.c \
		$(SRC_ENV)/env.c \
		$(SRC_ENV)/env_locals.c \
		$(SRC_ENV)/env_list.c \
		$(SRC_TOKEN)/token_type.c \
		$(SRC_TOKEN)/token_utils.c \
		$(SRC_TOKEN)/token_free.c \
		$(SRC_TOKEN)/token_list.c

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
