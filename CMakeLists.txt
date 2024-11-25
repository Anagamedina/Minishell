cmake_minimum_required(VERSION 3.28)
project(minishell C)

set(CMAKE_C_STANDARD 99)

# Anadir todos los archivos con sus rutas aqui:
file(GLOB INPUT_FILES src/input/*.c)
file(GLOB TOKENIZE_FILES src/tokenize/*.c)
file(GLOB COMMAND_FILES src/commands/*.c)
file(GLOB ENV_FILES src/env/*.c)
file(GLOB LIBFT_DIR libft/*.c)
file(GLOB MINI src/mini/*.c)
file(GLOB BUILTINS_ANA src/built-ins-1/*.c)
#file(GLOB BUILTINS_DARUNY src/builtins_part02/*.c)

include_directories(includes)

execute_process(
        COMMAND make
        # Directorio donde está tu Makefile
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(minishell
# main
        src/minishell.c
#        ${HEADERS}
        ${INPUT_FILES}
        ${TOKENIZE_FILES}
        ${COMMAND_FILES}
        ${ENV_FILES}
        ${LIBFT_DIR}
        ${BUILTINS_ANA}
        ${MINI}
)

# link with readline library
target_link_libraries(minishell readline)
