cmake_minimum_required(VERSION 3.28)
project(minishell C)

set(CMAKE_C_STANDARD 99)

add_executable(minishell
        src/minishell.c
)
