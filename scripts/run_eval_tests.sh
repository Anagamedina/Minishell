#!/bin/bash
set -euo pipefail

BIN=${1:-./minishell}

if [ ! -x "$BIN" ]; then
  echo "Build minishell first (make) or pass path to binary."
  exit 1
fi

echo "[Basics] echo, exit status"
printf "echo hello\nexit 0\n" | "$BIN" | tee /dev/null

echo "[Builtins] export/unset/env"
printf "export FOO=bar\necho $FOO\nunset FOO\necho $FOO\nexit\n" | "$BIN" | tee /dev/null

echo "[Redirections] >, >>, <"
printf "echo content > out.txt\ncat < out.txt\nexit\n" | "$BIN" | tee /dev/null

echo "[Pipes] simple pipeline"
printf "echo hello | tr a-z A-Z\nexit\n" | "$BIN" | tee /dev/null

echo "[Expansion] $? and $VAR"
printf "false\necho $?\nexport X=42\necho $X\nexit\n" | "$BIN" | tee /dev/null

echo "Done. Review outputs above."

echo "[Quotes] single vs double"
printf "export X=world\necho '$X'\necho \"$X\"\nexit\n" | "$BIN" | tee /dev/null

echo "[Long pipeline] echo 1 | cat | cat | cat | cat | cat"
printf "echo 1 | cat | cat | cat | cat | cat\nexit\n" | "$BIN" | tee /dev/null

echo "[Nested shell] run clean bash inside minishell"
printf "env -i bash --noprofile --norc -c 'echo FROM_NESTED'\nexit\n" | "$BIN" | tee /dev/null

echo "[Signals] SIGINT during execution (sleep 5 -> Ctrl+C)"
(
  { printf "sleep 5\n"; sleep 1; } | "$BIN" &
  MS_PID=$!
  sleep 1
  # send Ctrl+C (SIGINT) to minishell; it should terminate the running child with status 130
  kill -INT "$MS_PID" 2>/dev/null || true
  wait "$MS_PID" || true
) ; echo "(Check: sleep should have been interrupted)"

echo "[Signals] SIGQUIT during execution (yes | head)"
(
  { printf "yes | head -n 1000000\n"; sleep 1; } | "$BIN" &
  MS_PID=$!
  sleep 1
  # send Ctrl+\\ (SIGQUIT)
  kill -QUIT "$MS_PID" 2>/dev/null || true
  wait "$MS_PID" || true
) ; echo "(Check: status ~131 and message if implemented)"

echo "All scripted tests executed. Some signal tests may require manual verification."

