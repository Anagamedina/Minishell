### Minishell Evaluation Checklist

Use this list to guide functional testing and evaluation.

#### Basics
- Start/exit minishell (`Ctrl+D`, `exit` with/without status).
- Prompt behavior and history (`readline`, `add_history`).

Examples:
```bash
./minishell
# type and hit enter
echo hello
# Ctrl+D should exit without message (or as per project spec)
./minishell
exit
./minishell
exit 42   # shell should exit with status 42
```

#### Builtins
- `echo` (with `-n`), `pwd`, `cd` (relative/absolute, errors), `export` (show/add/update), `unset`, `env`, `exit` (numeric/non-numeric, too many args).

Examples:
```bash
echo hello world
echo -n no_newline; echo tail
pwd
cd /; pwd
cd does_not_exist   # should print error
export FOO=bar; echo $FOO
export FOO=baz; echo $FOO
unset FOO; echo $FOO   # empty
env | grep -E '^(PATH|HOME)='
exit 256   # normalized to 0-255 (256 -> 0)
exit foo   # numeric argument required (error + status 2 per bash behavior)
exit 1 2   # too many arguments
```

#### Redirections
- `<` input redirection (file exists / missing).
- `>` truncate output; `>>` append output.
- Combinations: multiple redirs, order precedence.

Examples:
```bash
echo content > out.txt
cat < out.txt
echo more >> out.txt; cat out.txt
cat < missing.txt    # error message
cat < out.txt > copy.txt; diff out.txt copy.txt
echo A > a.txt > b.txt; cat a.txt b.txt   # check which file has content
```

#### Heredoc `<<`
- Delimiter matching, variable expansion on/off (quoted vs unquoted delimiter).
- Interrupt with `Ctrl+C` (should abort heredoc, exit status 130).
- Multiple heredocs in same command.

Examples:
```bash
cat << EOF
line1
line2
EOF

# expansion enabled (unquoted delimiter)
export NAME=mini
cat << END
Hello $NAME
END

# expansion disabled (quoted delimiter)
cat << 'END'
Hello $NAME
END

# interrupt heredoc with Ctrl+C when prompting "> "
cat << STOP
^C
# minishell should set status 130 and not crash

# multiple heredocs
cat << A << B
first
A
second
B
```

#### Pipes
- Single and multiple pipes (`cmd1 | cmd2 | cmd3`).
- Redirections combined with pipes.

Examples:
```bash
echo hello | tr a-z A-Z
printf "a\nb\nc\n" | grep b | wc -l
cat < out.txt | grep content | wc -c > count.txt; cat count.txt
```

#### Expansion
- `$VAR`, `$?`, undefined vars, edge cases (`$1`, `$VAR_SUFFIX`).
- Quotes handling: single vs double, nested quotes behavior.

Examples:
```bash
export X=42; echo $X
false; echo $?   # should print non-zero
unset X; echo $X # empty
echo "$Xsuffix"  # expands X then literal suffix
echo '$X'        # no expansion
echo "mix '$X' and \"$X\""  # check behavior
```

#### Errors and Messages
- Command not found (127), permission denied, no such file or directory.
- Syntax errors (unclosed quotes, invalid token sequences).

Examples:
```bash
not_a_command
./minishell
"unclosed
echo >
cat < nofile
./no_exec_file   # create a file without +x to check permission denied
```

#### Signals
- `Ctrl+C` at prompt (no exit, prompt refresh).
- `Ctrl+C` during heredoc (abort 130).
- `Ctrl+C` during execution (child 130), `Ctrl+\` (131 with message).

Examples:
```bash
# at prompt: press Ctrl+C -> should show new prompt line
sleep 5    # press Ctrl+C -> terminated (status 130)
yes | head -n 1000000    # press Ctrl+\ -> 131 and message
```

#### Environment
- Inheritance of env from parent, `export`/`unset` effects, `PATH` resolution.

Examples:
```bash
env | grep USER=
export NEWVAR=ok; env | grep NEWVAR=
unset NEWVAR; env | grep NEWVAR=
ls  # resolved via PATH
```

#### Memory/FD Hygiene
- No leaks on normal usage and on error paths (valgrind).
- FDs closed properly; no descriptor leaks across pipelines.

Examples:
```bash
# run under valgrind (if allowed by subject) for a session of mixed commands
valgrind --leak-check=full --track-fds=yes ./minishell
```

#### Edge Cases
- Empty input, only spaces, tabs.
- Very long lines, many arguments.
- Commands with relative and absolute paths.

Examples:
```bash
"   "      # only spaces
printf 'a%.0s' {1..5000} | wc -c   # long line via pipe
./usr/bin/../bin/echo hello  # weird path resolution
./minishell    # from relative / absolute paths
```


