# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 17:34:21 by anamedin          #+#    #+#              #
#    Updated: 2024/11/04 12:18:27 by anamedin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR) #-fsanitize=address

SRC_DIR = src
INPUT_DIR = src/input
OBJ_DIR = obj
LIBFT_DIR = libft
MINISHELL_H = includes/minishell.h

SRC = 	$(SRC_DIR)/minishell.c \
		$(INPUT_DIR)/get_input.c \
		$(INPUT_DIR)/paths.c \
		$(INPUT_DIR)/free_errors.c \
		$(INPUT_DIR)/tests.c 

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))


LIBFT = $(LIBFT_DIR)/libft.a

# ==================================== #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MINISHELL_H) Makefile
	@mkdir -p $(dir $@)
# @mkdir -p $(OBJ_DIR)

	$(CC) $(CFLAGS) -c $< -o $@

# ==================================== #
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# ==================================== #
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
