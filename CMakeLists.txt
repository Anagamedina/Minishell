cmake_minimum_required(VERSION 3.28)
project(minishell C)

set(CMAKE_C_STANDARD 99)

# Anadir todos los archivos con sus rutas aqui:
file(GLOB INPUT_FILES src/input/*.c)
file(GLOB TOKENIZE_FILES src/tokenize/*.c)
file(GLOB COMMAND_FILES src/commands/*.c)
file(GLOB ENV_FILES src/env/*.c)
file(GLOB LIBFT_DIR libft/*.c)

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
# input
        ${INPUT_FILES}
# tokenize
        ${TOKENIZE_FILES}
# commands
        ${COMMAND_FILES}
# environment
        ${ENV_FILES}
        ${LIBFT_DIR}
        src/commands/errors_commands.c
)

# Enlazar con la biblioteca readline
target_link_libraries(minishell readline)
