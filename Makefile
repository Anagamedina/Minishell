# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By:  dasalaza < dasalaza@student.42barcel>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 17:34:21 by anamedin          #+#    #+#              #
#    Updated: 2024/12/28 12:53:06 by  dasalaza        ###   ########.fr        #
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
SRC_TOKENIZE = $(SRC_DIR)/tokenize
SRC_EXECUTE = $(SRC_DIR)/execute
SRC_BUILTINS1 = $(SRC_DIR)/built_ins_1
SRC_BUILTINS2 = $(SRC_DIR)/built_ins_2
SRC_CMD = $(SRC_DIR)/commands
SRC_EXPAND= $(SRC_DIR)/expand
OBJ_DIR = obj
LIBFT_DIR = libft
MINISHELL_H = includes/minishell.h 
TESTING_H = testing/testing.h

SRC =	$(SRC_MINI)/init_struct.c \
		$(SRC_INPUT)/input.c \
		$(SRC_DIR)/ft_string_utils.c \
		$(SRC_ENV)/env.c \
		$(SRC_ENV)/env_utils_locals.c \
		$(SRC_ENV)/env_locals_list.c \
		$(SRC_ENV)/free_env.c \
		$(SRC_TOKENIZE)/token_free.c \
		$(SRC_TOKENIZE)/token_split.c \
		$(SRC_TOKENIZE)/token_type.c \
		$(SRC_TOKENIZE)/token_utils.c \
		$(SRC_TOKENIZE)/token_utils_quotes.c \
		$(SRC_TOKENIZE)/token_utils_split.c \
		$(SRC_TOKENIZE)/token_utils_word_count.c \
		$(SRC_CMD)/cmd_init.c \
		$(SRC_CMD)/cmd_args.c \
		$(SRC_CMD)/cmd_free.c \
		$(SRC_CMD)/cmd_builtins.c \
		$(SRC_CMD)/cmd_errors.c \
		$(SRC_CMD)/print_cmd.c \
		$(SRC_BUILTINS1)/built_in_export.c \
		$(SRC_BUILTINS1)/built_in_utils.c \
		$(SRC_DIR)/built_ins_main.c \
		$(SRC_BUILTINS2)/builtin_cd.c \
		$(SRC_BUILTINS2)/builtin_exit.c \
		$(SRC_PARSER)/parser_syntax_dollar.c \
		$(SRC_PARSER)/parser_syntax_quotes.c \
		$(SRC_PARSER)/parser_not_expand_utils.c \
		$(SRC_PARSER)/parser_syntax_expand.c \
		$(SRC_EXPAND)/expand_func.c \
		$(SRC_EXPAND)/expand_utils.c \
		$(SRC_EXECUTE)/free_errors.c \
		$(SRC_EXECUTE)/exce_paths.c \
		$(SRC_EXECUTE)/exce_init.c \
		$(SRC_EXECUTE)/exce_type.c \
		$(SRC_EXECUTE)/exce_cmd.c \
		$(SRC_EXECUTE)/get_input.c \
		$(SRC_EXECUTE)/tests.c

#		$(SRC_REDIR)/heredoc.c
#		$(SRC_EXECUTE)/get_inputc \
#		$(SRC_REDIR)/redir_syntax.c \
#		$(SRC_REDIR)/redir_file.c
SRC_WITH_MAIN = $(SRC) $(SRC_DIR)/minishell.c
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_WITH_MAIN))

LIBFT = $(LIBFT_DIR)/libft.a

# ==================================== #

TEST_SRC =	testing/test_main.c \
			testing/unity.c \
			testing/setup_testing.c \
			testing/test_remove_quotes.c \
			testing/test_double_quotes.c

OBJ_TEST = $(patsubst testing/%.c, $(OBJ_DIR)/testing/%.o, $(TEST_SRC))
OBJ_TESTING = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))  # Sin main.c

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

obj/testing/%.o: testing/%.c $(TESTING_H)
	@mkdir -p $(dir $@)
	$(CC)  -c $< -o $@
	#$(CC) $(CFLAGS) -c $< -o $@


test: $(OBJ_TEST) $(OBJ_TESTING)
	$(CC) -o testing_shell -Iincludes -I$(LIBFT_DIR) \
	$(OBJ_TESTING) $(OBJ_TEST) $(LIBFT) -lreadline

# ==================================== #

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR) obj/testing

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) testing_shell

re: fclean all

.PHONY: all clean fclean re test
