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
#CFLAGS = -Iincludes  -I$(LIBFT_DIR) #-fsanitize=address
CFLAGS = -Wall -Wextra -Werror -Iincludes -I$(LIBFT_DIR) #-fsanitize=address

SRC_DIR = src
SRC_ENV= $(SRC_DIR)/env
SRC_MINI= $(SRC_DIR)/mini
SRC_INPUT= $(SRC_DIR)/input
SRC_PARSER= $(SRC_DIR)/parser
SRC_REDIR= $(SRC_DIR)/redir
SRC_TOKEN = $(SRC_DIR)/tokenize
SRC_BUILTINS1 = $(SRC_DIR)/built_ins_1
SRC_BUILTINS2 = $(SRC_DIR)/built_ins_2
SRC_CMD = $(SRC_DIR)/commands
SRC_EXPAND= $(SRC_DIR)/expand
OBJ_DIR = obj
LIBFT_DIR = libft
MINISHELL_H = includes/minishell.h

SRC =	$(SRC_MINI)/init_struct.c \
		$(SRC_INPUT)/input.c \
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
		$(SRC_BUILTINS2)/builtin_exit.c \
		$(SRC_PARSER)/parser_syntax_dollar.c \
		$(SRC_PARSER)/parser_syntax_quotes.c \
		$(SRC_PARSER)/parser_not_expand_utils.c \
		$(SRC_PARSER)/parser_syntax_expand.c \
		$(SRC_EXPAND)/expand_func.c \
		$(SRC_EXPAND)/expand_utils.c \
		$(SRC_REDIR)/input_redir.c \
		$(SRC_REDIR)/redir_syntax.c \
		$(SRC_REDIR)/redir_file.c
#		$(SRC_REDIR)/heredoc.c

SRC_WITH_MAIN = $(SRC) $(SRC_DIR)/minishell.c
#SRC_TESTING = $(SRC) testing/test_main.c
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_WITH_MAIN))

OBJ_TESTING = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT = $(LIBFT_DIR)/libft.a

# ==================================== #

TEST_SRC = testing/test_main.c testing/unity.c
TEST_OBJ = $(patsubst %.c, $(OBJ_DIR)/testing/%.o, $(notdir $(TEST_SRC)))

# ==================================== #

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(MINISHELL_H) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

# ==================================== #

obj/testing/%.o: testing/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJ)
	$(CC) -o testing_shell -Iincludes -I$(LIBFT_DIR) \
	$(OBJ_TESTING) $(TEST_OBJ) $(LIBFT) -lreadline

# ==================================== #
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) obj/testing

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) testing_shell

re: fclean all

.PHONY: all clean fclean re test
