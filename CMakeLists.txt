# version 3.28 -> clion && version 3.22.1 -> vscode

# cmake_minimum_required(VERSION 3.28)
cmake_minimum_required(VERSION 3.22.1)
project(minishell C)

set(CMAKE_C_STANDARD 99)

# Anadir todos los archivos con sus rutas aqui:
file(GLOB INPUT_FILES src/input/*.c)
file(GLOB TOKENIZE_FILES src/tokenize/*.c)
file(GLOB COMMAND_FILES src/commands/*.c)
file(GLOB ENV_FILES src/env/*.c)
file(GLOB LIBFT_DIR libft/*.c)
file(GLOB MINI src/mini/*.c)
file(GLOB BUILTINS_ANA src/built_ins_1/*.c)
file(GLOB BUILTINS_DARUNY src/built_ins_2/*.c)
file(GLOB PARSER_DIR src/parser/*.c)

include_directories(includes)

execute_process(
        COMMAND make
        # Directorio donde está tu Makefile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(minishell
        src/minishell.c
        ${INPUT_FILES}
        ${TOKENIZE_FILES}
        ${COMMAND_FILES}
        ${ENV_FILES}
        ${LIBFT_DIR}
        ${BUILTINS_ANA}
        ${MINI}
        src/built_ins_main.c
        ${BUILTINS_DARUNY}
        ${PARSER_DIR}
        src/expand/expand_func.c
)

# link with readline library
target_link_libraries(minishell readline)
