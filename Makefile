# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anamedin <anamedin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/01 17:34:21 by anamedin          #+#    #+#              #
#    Updated: 2025/03/04 11:50:37 by anamedin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc #-O1 #-v
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
SRC_FREE= $(SRC_DIR)/free
SRC_SIGNALS= $(SRC_DIR)/signals

OBJ_DIR = obj
LIBFT_DIR = libft
MINISHELL_H = includes/minishell.h 
TESTING_H = testing/testing.h

SRC =	$(SRC_MINI)/init_minishell.c \
		$(SRC_MINI)/env_setup.c \
		$(SRC_INPUT)/input.c \
		$(SRC_DIR)/ft_string_utils.c \
		$(SRC_ENV)/env.c \
		$(SRC_ENV)/env_utils.c \
		$(SRC_ENV)/init_env_list.c \
		$(SRC_TOKENIZE)/token_split.c \
		$(SRC_TOKENIZE)/token_type.c \
		$(SRC_TOKENIZE)/token_utils.c \
		$(SRC_TOKENIZE)/token_utils_quotes.c \
		$(SRC_TOKENIZE)/token_utils_split.c \
		$(SRC_TOKENIZE)/token_utils_word_count.c \
		$(SRC_CMD)/cmd_init.c \
		$(SRC_CMD)/cmd_args.c \
		$(SRC_CMD)/cmd_free.c \
		$(SRC_CMD)/cmd_errors.c \
		$(SRC_CMD)/cmd_list.c \
		$(SRC_CMD)/cmd_init_utils.c \
		$(SRC_CMD)/print_cmd.c \
		$(SRC_BUILTINS1)/built_in_export.c \
		$(SRC_BUILTINS1)/built_in_unset.c \
		$(SRC_BUILTINS1)/built_in_utils.c \
		$(SRC_BUILTINS1)/builtin_echo.c \
		$(SRC_BUILTINS1)/builtin_part_one_utils.c \
		$(SRC_BUILTINS1)/export_utils.c \
		$(SRC_DIR)/built_ins_main.c \
		$(SRC_BUILTINS2)/builtin_cd.c \
		$(SRC_BUILTINS2)/builtin_exit.c \
		$(SRC_BUILTINS2)/builtin_exit_utils.c \
		$(SRC_BUILTINS2)/builtin_exit_utils.c \
		$(SRC_BUILTINS2)/builtin_pwd.c \
		$(SRC_PARSER)/parser_check_quotes_dollar.c \
		$(SRC_PARSER)/parser_expand_cases.c \
		$(SRC_PARSER)/parser_expand_dollar.c \
		$(SRC_PARSER)/parser_expand_utils.c \
		$(SRC_PARSER)/parser_syntax.c \
		$(SRC_PARSER)/parser_init_quotes.c \
		$(SRC_PARSER)/parser_not_expand.c \
		$(SRC_PARSER)/parser_tab.c \
		$(SRC_PARSER)/parser_tokens.c \
		$(SRC_PARSER)/parser_utils.c \
		$(SRC_PARSER)/parser_input.c \
		$(SRC_PARSER)/parser_handle_not_expand.c \
		$(SRC_PARSER)/parser_borrador.c \
		$(SRC_EXPAND)/expand_env.c \
		$(SRC_EXPAND)/expand_merge.c \
		$(SRC_EXPAND)/expand_split.c \
		$(SRC_EXPAND)/expand_token_utils.c \
		$(SRC_EXPAND)/expand_vars.c \
		$(SRC_EXECUTE)/exce_paths.c \
		$(SRC_EXECUTE)/exce_init.c \
		$(SRC_EXECUTE)/exce_type.c \
		$(SRC_EXECUTE)/exce_cmd.c \
		$(SRC_EXECUTE)/exce_errors.c \
		$(SRC_EXECUTE)/excec_pipeline.c \
		$(SRC_EXECUTE)/exce_cmd_utils.c \
		$(SRC_EXECUTE)/exce_utils.c \
		$(SRC_EXECUTE)/tests.c \
		$(SRC_REDIR)/redir_file.c \
		$(SRC_REDIR)/redir_init.c \
		$(SRC_REDIR)/redir_utils.c \
		$(SRC_REDIR)/heredoc.c \
		$(SRC_REDIR)/redir_syntax.c \
		$(SRC_FREE)/free_cmd.c \
		$(SRC_FREE)/free_env.c \
		$(SRC_FREE)/free_exec.c \
		$(SRC_FREE)/free_mini.c \
		$(SRC_FREE)/free_redir.c \
		$(SRC_FREE)/free_split.c \
		$(SRC_FREE)/free_tokens.c \
		$(SRC_SIGNALS)/signals.c \
		$(SRC_SIGNALS)/signals_utils.c

#		$(SRC_EXECUTE)/tests.c \
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
