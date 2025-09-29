### README: Módulo `execute/`

Responsable: Ana Gabriela Medina

#### Objetivo
Coordinar la ejecución de comandos (builtins y externos), crear pipes entre procesos, aplicar redirecciones y gestionar estados/salidas.

#### Piezas principales
- `exce_pipeline.c`: orquesta el pipeline (crea pipes, forkea, espera hijos).
- `exce_pipeline_child.c`: lógica del hijo (heredoc, redirecciones, exec).
- `exce_cmd.c`: ejecución en padre de ciertos builtins, helpers de redirección de stdout temporal.
- `exce_cmd_utils.c`: `execve` y duplicación de FDs (`redirect_in/out`).
- `exce_cmd_type.c`: detección de builtin y resolución de comando externo.
- `exce_paths.c`: resolución de `PATH` para encontrar ejecutables.
- `exce_init.c`: inicialización de `t_exec`.
- `exce_utils.c`/`exce_errors.c`: utilidades y manejo de errores.

#### Flujo simplificado
1) `execute_commands(mini)` recorre comandos, configura FDs y forkea por comando.
2) En el hijo: `heredoc`, `apply_redirections`, `execute_builtin_or_external`.
3) En el padre: cierra FDs innecesarios y encadena pipes.
4) `wait_children(mini)` fija `exit_status` (130/131 si señales).

#### Notas
- Heredoc se ejecuta en proceso hijo separado; en SIGINT se retorna 130 y se aborta el resto.
- Redirecciones se aplican antes del `execve`.

Para más detalle, ver `docs/heredoc_flow.md` y `docs/signals_flow.md`.

