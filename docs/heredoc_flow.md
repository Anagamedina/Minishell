### Flujo detallado del Heredoc

Este documento explica paso a paso cómo se implementa el heredoc (`<<`) en el proyecto, incluyendo un diagrama del flujo en Mermaid.

---

#### 1) Detección y preparación
- El parser crea redirecciones de tipo `HEREDOC` en la lista `cmd->redir_list`.
- `heredoc(t_cmd *cmd)` recorre las redirecciones; por cada `HEREDOC`:
  - Decide si expandir variables según las comillas del delimitador.
  - Hace `fork()` para crear un proceso dedicado al heredoc.

---

#### 2) Proceso hijo (lector)
- Configura `setup_signals(HERE_DOC, NULL)`.
- `create_heredoc(...)`:
  - Genera nombre `/tmp/heredoc<N>`.
  - Abre el temporal con `open_file(..., HEREDOC)`.
  - Llama a `write_heredoc_content(fd, delimiter, expand_vars)` que hace:
    - Bucle `readline(" > ")` hasta que la línea coincide con `delimiter` o EOF.
    - Expande variables si procede, escribe cada línea en el temporal.
  - Sustituye `redir->filename` por la ruta del temporal.
- Sale con `exit(0)` si todo fue bien, `exit(1)` si hubo error; `Ctrl+C` provoca `exit(130)` por el handler.

---

#### 3) Proceso padre (coordinador)
- `waitpid()` al hijo del heredoc.
- Si `SIGINT` (130) o `exit != 0`:
  - Aborta el resto de heredocs.
  - Hace que `heredoc(cmd)` retorne `-1`.
- Si todo OK continúa con el siguiente heredoc del comando.

---

#### 4) Uso del temporal como STDIN
- En la fase de redirecciones (`apply_redirections`), una redirección de entrada abrirá el fichero `redir->filename` (que ahora es `/tmp/heredoc<N>`) y lo asociará a `STDIN_FILENO`.

---

#### 5) Diagrama de flujo (Mermaid)

```mermaid
flowchart TD
  A[Iterar redirecciones] --> B{tipo == HEREDOC}
  B -- "no" --> A
  B -- "si" --> C[fork()]
  C -->|child| D[setup_signals(HERE_DOC)]
  D --> E[create_heredoc]
  E --> F{ok?}
  F -- "si" --> G[exit(0)]
  F -- "no" --> H[exit(1)]
  C -->|parent| I[waitpid()]
  I --> J{"SIGINT o exit != 0"}
  J -- "si" --> K[return -1]
  J -- "no" --> L[next redir]

```

---

#### 6) Consideraciones
- Limpiar temporales en la fase de `free_exec` o al finalizar el pipeline.
- Unificar la configuración de señales: en heredoc solo en el hijo.
- Asegurar que `exit_status` se fija a 130 si el heredoc se aborta por `Ctrl+C`.


