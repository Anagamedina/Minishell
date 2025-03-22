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

## Technical Requirements

- Use of the `libft` library and authorized specific functions.
- Memory management to prevent leaks (except for `readline`, as specified).


## 📌 **Important Notes & Useful Commands**

### 🔹 **Running Bash without Environment Variables or Configurations**

```plaintext
env -i bash --noprofile --norc
```

**What does this command do?**  
It runs **Bash in a clean environment**, without loading configurations or inheriting variables from the current environment.

#### **📌 Breakdown of the Command:**
- **`env -i`** (`--ignore-environment`)
    - Starts a new **empty environment**, without inheriting variables like `PATH`, `HOME`, `USER`.
    - Useful for testing or debugging without inherited configurations.

- **`bash --noprofile --norc`**
    - **`--noprofile`** → Does not load `~/.bash_profile`, `~/.bash_login`, or `/etc/profile`.
    - **`--norc`** → Does not execute `~/.bashrc`, avoiding custom configurations.

### **📌 Example Usage**

To verify that the environment is indeed empty, run:

```sh
  env -i bash --noprofile --norc
  env
```

**Expected Output:** (No environment variables loaded)
```sh
  # No environment variables will be displayed
```

---

## ENVIRONMENT VARIABLES TO INITIALIZE

### **📌 Environment Configuration in Minishell**

This section describes the **environment variables** that are initialized if they don't exist when running **Minishell**, based on our `configure_shell_env()` function.

---

## **🔹 Initialized Environment Variables**
Minishell checks and creates the following variables if they don't exist in the environment:

| **Variable** | **Purpose** | **Default Value if Not Present** |
|--------------|-------------|----------------------------------|
| `OLDPWD`     | Stores the previous directory for `cd -` | `""` (empty until `cd` modifies it) |
| `PATH`       | Defines directories to search for executable commands | `"/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin"` |
| `HOME`       | User's home directory | Value of `getenv("HOME")` or `"/home/"` if not found |
| `USER`       | Current user's name | `getenv("USER")` or `"unknown"` if not found |
| `SHLVL`      | Shell level, increases with each new instance | If `SHLVL >= 100`, resets to `"1"` |

---

## **🔹 Special Handling of `OLDPWD` and `PWD`**
### **Should `OLDPWD` be reset to `""` or remain?**
- If `OLDPWD` already exists with a valid path, **it remains unchanged**.
- If `OLDPWD` does not exist, **it is initialized to `""` (empty)** until `cd` updates it.

### **How does `PWD` behave?**
- `PWD` **remains as is**, as it represents the current directory.
- Bash also keeps it if it exists in `env`.

---

## **🔹 Handling of `SHLVL`**
1. If `SHLVL` **does not exist or is negative**, it is initialized to `0`.
2. If `SHLVL >= 100`, **a warning is displayed, and it is reset to `1`**.
3. In other cases, **it is incremented by `+1`**.

Example warning message if `SHLVL >= 100`:
```sh
mish: warning: shell level (100) too high, resetting to 1
```

---

## **📌 How does this behave in Bash?**
Running **Bash in an empty environment** (`env -i bash --noprofile --norc`), we get:
```sh
  PWD=/home/user
  SHLVL=1
  _=/usr/bin/env
```

➡️ **Minishell replicates this behavior, ensuring compatibility.**

---

🚀 **With this implementation, Minishell handles the environment efficiently and is compatible with Bash.**

---

**We hope this shell becomes an effective and user-friendly tool for interacting with the system.**

Thank you for reviewing our project, and feel free to contact us with any questions or suggestions!

---

Este formato hace que el contenido sea más legible y estructurado. Las secciones están claramente divididas con títulos descriptivos, lo que facilita la navegación.