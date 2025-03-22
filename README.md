# Minishell Project

Developed by:
- [Ana](https://github.com/Anagamedina)
- [Daruny](https://github.com/Daruuu)

This project aims to create a functional shell that interprets and executes commands similar to Bash, meeting the fundamental requirements of 42 School.

## Objective
The shell should provide an interactive experience, support essentially such as redirections and pipelines, and manage variables and signals, all with a focus on efficiency and memory management.

### Structure of Different Lists Used in Minishell

The following diagram illustrates all the linked lists used in the project and how they are interconnected.

<img src="https://raw.githubusercontent.com/Anagamedina/Minishell/main/docs/images/structure_list.png" width="500" height="500">

### Program Flow in Minishell

Diagram showing the execution flow, from input processing to command execution and output handling.

<img src="https://raw.githubusercontent.com/Anagamedina/Minishell/main/docs/images/flow_minishell.png" width="500" height="500">


## Project Structure

The project includes a **Makefile** to simplify the compilation process files to ensure a clear, modular structure.
Additionally, the documentation is stored in the `docs` folder for easy reference.

### Key Folders and Files:

- **`docs/`**: Contains documentation files and notes and other useful documents.

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











