### README: Módulo `redir/`

Responsable: Ana Gabriela Medina

#### Objetivo
Gestionar redirecciones de entrada y salida, y la funcionalidad `heredoc`.

#### Piezas principales
- `heredoc.c`: creación y lectura de heredoc en proceso hijo; escribe a `/tmp/heredoc<N>` y sustituye `redir->filename`.
- `redir_file.c`: `open_file` por tipo y `apply_redirections` para aplicar `<`, `>`, `>>`, y `HEREDOC`.
- `redir_utils.c`: helpers de FDs y generación de nombres temporales.
- `redir_init.c`: inicialización y agregado de estructuras `t_redir` a `t_cmd`.
- `redir_expand.c`: expansión de variables dentro del heredoc si procede.

#### Flujo heredoc (resumen)
1) Por cada `<<`, se forkea un hijo con señales `HERE_DOC`.
2) El hijo lee con `readline(" > ")` hasta el delimitador y escribe en `/tmp/heredoc<N>`.
3) El padre espera: si SIGINT, aborta y retorna error; si OK, continúa.
4) Al aplicar redirecciones, `<` o `HEREDOC` abren el temporal como `STDIN`.

Diagrama y detalle en `docs/heredoc_flow.md`.

