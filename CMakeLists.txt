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
file(GLOB EXPAND_DIR src/expand/*.c)
file(GLOB PARSER_DIR src/parser/*.c)
file(GLOB UNIT_C_TESTING tests/*.c)

include_directories(includes)
include_directories(tests/unity.h)
include_directories(tests/unity_internals.h)

execute_process(
        COMMAND make
        # Directorio donde está tu Makefile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(minishell
        src/minishell.c
        src/built_ins_main.c
        ${INPUT_FILES}
        ${TOKENIZE_FILES}
        ${COMMAND_FILES}
        ${ENV_FILES}
        ${LIBFT_DIR}
        ${BUILTINS_ANA}
        ${MINI}
        ${BUILTINS_DARUNY}
        ${PARSER_DIR}
        ${EXPAND_DIR}
        ${UNIT_C_TESTING}
)

# link with readline library
target_link_libraries(minishell readline)
