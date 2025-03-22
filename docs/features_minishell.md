## Technical Requirements

- Use of the `libft` library and authorized specific functions.
- Memory management to prevent leaks (except for `readline`, as specified).

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

