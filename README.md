# Minishell Project

Developed by:
- [Ana](https://github.com/Anagamedina)
- [Daruny](https://github.com/Daruuu)

This project aims to create a functional shell that interprets and executes commands similar to Bash, meeting the fundamental requirements of 42 School.

## Objective
The shell should provide an interactive experience, support essentially such as redirections and pipelines, and manage variables and signals, all with a focus on efficiency and memory management.

## Project Structure

The project includes a **Makefile** to simplify the compilation process files to ensure a clear, modular structure.
Additionally, the documentation is stored in the `docs` folder for easy reference.

### Key Folders and Files:
- **`docs/`**: Contains documentation files, including the `README.md`, project diagrams, and other useful documents.

- **`src/`**: Contains the source code of the project, divided into functional folders:
    - **`built_ins_1/`** and **`built_ins_2/`**: Handle internal commands like `echo`, `cd`, `pwd`, `export`, `unset`, etc.
    - **`commands/`**: Contains functions for handling command arguments and execution.
    - **`env/`**: Manages environment variables and their setup.
    - **`execute/`**: Responsible for executing commands, including handling pipes and redirections.
    - **`expand/`**: Handles variable and environment variable expansions.
    - **`free/`**: Manages memory freeing functions for various structures.
    - **`input/`**: Deals with input parsing and terminal interaction.
    - **`parser/`**: Contains functions for parsing input, managing quotes, and handling tokens.
    - **`redir/`**: Manages redirections, including input/output redirection and heredoc.
    - **`signals/`**: Handles signal management (e.g., `Ctrl+C`, `Ctrl+D`).
    - **`tokenize/`**: Responsible for tokenizing input and handling special characters.

- **`libft/`**: Custom library used for string manipulation and other utility functions.

- **`testing/`**: Contains test files and testing utilities, including scripts and Unity framework setup for unit tests.

### Important Files:
- **`Makefile`**: Automates the build process.
- **`minishell.c`**: Main entry point for the shell program.
- **`README.md`**: Provides an overview of the project, its functionality, and setup instructions.
- **`test_builtins.sh`**: A shell script to test built-in commands.
- **`pipes_test.sh`**: Tests the functionality of pipes in the shell.












## Features

### User Interface
- Displays a prompt while waiting for commands.
- Maintains a functional history to remember previous commands.

### Command Execution
- Locates and executes commands using `PATH` or relative and absolute paths.
- Implements redirections:
    - Input (`<`)
    - Output (`>`, `>>`)
    - Heredoc (`<<`)
- Supports pipelines (`|`) to chain commands together.

### Variables and Environment
- Expands environment variables (`$` and `$?`).
- Manages single and double quotes, respecting rules for metacharacters(ASCII).

### Signal Handling
- Handles `ctrl-C`, `ctrl-D`, and `ctrl-\` signals like in Bash, with specific effects for interactive mode.
- Uses a single global(if is necessary) variable to store the signal number.

### Built-ins
The shell includes essential built-in commands:

- `echo` with `-n` option
- `cd` to change directories
- `pwd` to display the current directory
- `export` to manage environment variables
- `unset` to remove environment variables
- `env` to display environment variables
- `exit` to exit the shell

