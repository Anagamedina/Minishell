cmake_minimum_required(VERSION 3.22.1)

# version 3.28 -> clion && version 3.22.1 -> vscode
project(minishell C)

set(CMAKE_C_STANDARD 99)

# Habilitar sanitizers para depuración
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address,undefined -g")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")

# setup the dirs and files here:
file(GLOB INPUT_DIR src/input/*.c)
file(GLOB TOKENIZE_DIR src/tokenize/*.c)
file(GLOB COMMAND_DIR src/commands/*.c)
file(GLOB ENV_DIR src/env/*.c)
file(GLOB LIBFT_DIR libft/*.c)
file(GLOB MINI src/mini/*.c)
file(GLOB BUILTINS_ANA src/built_ins_1/*.c)
file(GLOB BUILTINS_DARUNY src/built_ins_2/*.c)
file(GLOB EXPAND_DIR src/expand/*.c)
file(GLOB PARSER_DIR src/parser/*.c)
file(GLOB UNIT_C_TESTING testing/*.c)
file(GLOB EXECUTE_DIR src/execute/*.c)
file(GLOB FREE_DIR src/free/*.c)

# include the headers
include_directories(includes)
include_directories(testing)
include_directories(free)

# compile Makefile of libft if it's not compiled
execute_process(
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/libft
)

# *********** Executable: minishell **********

add_executable(minishell
        src/minishell.c
        src/built_ins_main.c
        src/ft_string_utils.c
        ${INPUT_DIR}
        ${TOKENIZE_DIR}
        ${COMMAND_DIR}
        ${ENV_DIR}
        ${LIBFT_DIR}
        ${MINI}
        ${BUILTINS_ANA}
        ${BUILTINS_DARUNY}
        ${EXPAND_DIR}
        ${PARSER_DIR}
        ${EXECUTE_DIR}
        ${FREE_DIR}
)
# link with readline library
target_link_libraries(minishell readline)

# *********** Executable: tesing_minishell **********

add_executable(testing_shell
        ${UNIT_C_TESTING}
        src/ft_string_utils.c
        src/built_ins_main.c
        ${INPUT_DIR}
        ${TOKENIZE_DIR}
        ${COMMAND_DIR}
        ${ENV_DIR}
        ${LIBFT_DIR}
        ${MINI}
        ${BUILTINS_ANA}
        ${BUILTINS_DARUNY}
        ${EXPAND_DIR}
        ${PARSER_DIR}
        ${EXECUTE_DIR}
        ${FREE_DIR}
)
# link with readline library
target_link_libraries(testing_shell readline)
