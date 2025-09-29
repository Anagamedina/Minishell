### Apuntes: Implementación de Heredoc en Minishell

Estos son mis apuntes para recordar cómo está implementado el heredoc en este proyecto y poder explicarlo a una compañera.

---

#### 1) ¿Qué es `heredoc` y qué hace en nuestro flujo?
- **Objetivo**: capturar líneas desde el usuario hasta un delimitador y guardarlas en un fichero temporal para usarlas como entrada estándar del comando.
- **Dónde se gestiona**: funciones principales en `src/redir/heredoc.c` y utilidades en `src/redir/redir_utils.c`.

Funciones clave:
- `write_heredoc_content(int fd_tmp, char *delimiter, int expand_vars)`
- `create_heredoc(t_redir *redir, int nbr_heredoc, int expand_vars)`
- `heredoc(t_cmd *cmd)`
- Señales: `setup_signals(HERE_DOC, ...)` y handlers en `src/signals/signals.c` y `src/signals/signals_utils.c`.

---

#### 2) ¿Por qué usamos `readline`?
- **Motivo**: `readline(" > ")` ofrece una experiencia interactiva (historial, edición de línea) y detecta bien `Ctrl+C`/`Ctrl+D`.
- En `write_heredoc_content` se hace un bucle: pedir línea con prompt "> ", comparar con el `delimiter`, y si no coincide, se escribe en el fichero temporal (con o sin expansión de variables según el caso).

Referencia:
```21:37:src/redir/heredoc.c
setup_signals(HERE_DOC, NULL);
line = readline("> ");
while (line && ft_strcmp(line, delimiter) != 0)
{
    if (expand_vars)
        expand_line = expand_variables(line);
    else
        expand_line = ft_strdup(line);
    if (expand_line)
    {
        ft_putendl_fd(expand_line, fd_tmp);
        free(expand_line);
    }
    free(line);
    line = readline("> ");
}
return (free(line), 0);
```

---

#### 3) ¿Por qué usamos `fork` para el heredoc?
- **Idea**: manejar `Ctrl+C` (SIGINT) de forma aislada mientras se lee el heredoc. Si el usuario interrumpe, queremos abortar solo la captura del heredoc sin tumbar el shell principal.
- En este repo existe `child_heredoc(...)` que crea un hijo con `fork()`, configura señales para modo HERE_DOC, ejecuta `create_heredoc(...)` y el padre hace `waitpid`. Si el hijo termina por SIGINT, el padre simplemente retorna.

Referencia:
```62:88:src/redir/heredoc.c
pid = fork();
if (pid == 0)
{
    setup_signals(HERE_DOC, mini);
    if (create_heredoc(redir, 0, 1) == -1)
        exit(1);
    exit(0);
}
else
{
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
        return ;
}
```

Nota: Actualmente `heredoc(t_cmd *cmd)` recorre las redirecciones y llama directamente a `create_heredoc(...)` sin `fork`. `child_heredoc` parece ser una alternativa diseñada para aislar señales; conviene decidir un único enfoque y usarlo de forma consistente.

---

#### 4) ¿Cómo gestionamos las redirecciones del heredoc?
- **Fichero temporal**: usamos `/tmp/heredoc<N>` como destino de lo que escribe el usuario.
  - `generate_heredoc_filename(nbr_heredoc)` en `redir_utils.c` crea nombres únicos.
  - `open_file(tmp_name, HEREDOC)` abre el descriptor para escritura.
- **Persistencia en la estructura**: tras escribir, sustituimos `redir->filename` por la ruta del temporal. Luego, cuando apliquemos la redirección de entrada del comando, abriremos este fichero como `STDIN`.

Referencia:
```54:67:src/redir/redir_utils.c
char	*generate_heredoc_filename(int nbr_heredoc)
{
    char	*num_str;
    char	*tmp_name;

    num_str = ft_itoa(nbr_heredoc);
    if (!num_str)
        return (NULL);
    tmp_name = ft_strjoin("/tmp/heredoc", num_str);
    free(num_str);
    if (!tmp_name)
        return (NULL);
    return (tmp_name);
}
```

Referencia a cómo se crea y guarda el temporal:
```45:59:src/redir/heredoc.c
tmp_name = generate_heredoc_filename(nbr_heredoc);
fd_tmp = open_file(tmp_name, HEREDOC);
write_heredoc_content(fd_tmp, redir->filename, expand_vars);
close(fd_tmp);
free(redir->filename);
redir->filename = ft_strdup(tmp_name);
free(tmp_name);
```

Después, en la fase de preparación de ejecución, la redirección de entrada usará `open_file(..., REDIR_IN)` sobre ese nombre para conectar al `STDIN` del proceso del comando.

---

#### 5) Señales en el heredoc: idea y handlers
- Modos de señales definidos en `setup_signals(mode, ...)`:
  - `PARENT`: `SIGINT` reimprime prompt; `SIGQUIT` ignorado.
  - `CHILD`: `SIGINT` imprime salto de línea; `SIGQUIT` imprime salto de línea personalizado.
  - `HERE_DOC`: `SIGINT` aborta heredoc con código 130; `SIGQUIT` ignorado.

Handlers relevantes:
```27:34:src/signals/signals_utils.c
void	handle_signal_heredoc(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        exit(130);
    }
}
```

Configuración de modos:
```56:66:src/signals/signals.c
if (mode == PARENT)
    return (setup_parent_signals());
else if (mode == CHILD)
    return (setup_child_signals());
else if (mode == HERE_DOC)
    return (setup_here_doc_signals());
```

---

#### 6) Posibles puntos a revisar/errores habituales
- **Doble configuración de señales**: `write_heredoc_content` llama a `setup_signals(HERE_DOC, NULL)` y, si se usa `child_heredoc`, el hijo también hace `setup_signals(HERE_DOC, mini)`. No es grave, pero conviene unificar dónde se fijan señales del modo HERE_DOC (idealmente solo en el proceso que lee).
- **Inconsistencia de diseño**: existe `child_heredoc(...)` pero `heredoc(t_cmd *cmd)` no forkea. Decidir un único patrón:
  - O bien: siempre en un hijo para capturar `SIGINT` sin afectar al padre.
  - O bien: en el mismo proceso, pero entonces `SIGINT` debe dejar el shell en estado coherente.
- **Limpieza de temporales**: asegurar que los `/tmp/heredoc<N>` se eliminan al finalizar el pipeline/comando si procede, para no dejar basura.
- **Expansión de variables**: se controla con `expand_vars` según comillas en el delimitador. Verificar que el parser marca correctamente el tipo y el `filename`/`delimiter` para decidir expansión.

---

#### 7) Resumen rápido 
- Leemos líneas con `readline` hasta ver el delimitador; las escribimos en un fichero temporal en `/tmp`.
- Ese temporal se convierte en la nueva entrada estándar del comando que tenía `<<`.
- Usamos señales específicas en modo HERE_DOC: `Ctrl+C` aborta solo el heredoc (código 130) y no mata el shell.
- Opcionalmente podemos hacerlo en un proceso hijo (con `fork`) para aislar mejor el manejo de `SIGINT`.


