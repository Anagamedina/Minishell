# Minishell

Autoras/es:
- [Ana Gabriela Medina](https://github.com/Anagamedina)
- [Darunny Salazar](https://github.com/Daruuu)

Proyecto de 42: implementación de una shell mínima compatible con lo esencial de Bash.

## Objetivo
Proveer una experiencia interactiva con tuberías, redirecciones, expansión de variables y gestión correcta de señales, priorizando claridad, modularidad y manejo de memoria.

## Reparto de trabajo
- En equipo: estructura del proyecto, parser, tokenize, expand y señales.
- División posterior:
  - Darunny: builtins y entorno (`env`).
  - Ana: ejecución (`execute`) y redirecciones (`redir`).

## Cómo compilar y ejecutar
```bash
make
./minishell
```
Para tests y scripts, ver `scripts/` y `testing/`.

### Estructuras de listas en Minishell

Diagrama de todas las listas enlazadas utilizadas y su relación.

<img src="https://raw.githubusercontent.com/Anagamedina/Minishell/main/docs/images/structure_list.png" width="500" height="500">

### Flujo del programa

Del input a la ejecución y salida:

<img src="https://raw.githubusercontent.com/Anagamedina/Minishell/main/docs/images/tokenize_and_validate_01.png" >

<img src="https://raw.githubusercontent.com/Anagamedina/Minishell/main/docs/images/execute.png">

## Estructura del proyecto

Usamos **Makefile** y una estructura modular. La documentación está en `docs/` (ver `docs/signals_flow.md` y `docs/heredoc_flow.md`).

### Carpetas clave

- `docs/`: documentación, notas y diagramas.
- `src/`: módulos de código fuente:
  - `built_ins_1/` y `built_ins_2/`: builtins (`echo`, `cd`, `pwd`, `export`, `unset`, ...).
  - `commands/`: argumentos y preparación de comandos.
  - `env/`: variables de entorno y conversión a matriz.
  - `execute/`: ejecución, pipes y coordinación de procesos.
  - `expand/`: expansión de variables.
  - `free/`: liberación de estructuras.
  - `input/`: lectura y preparación de entrada.
  - `parser/`: parsing de tokens, quotes y sintaxis.
  - `redir/`: redirecciones y heredoc.
  - `signals/`: configuración y handlers de señales.
  - `tokenize/`: tokenización.

### Archivos importantes
- `Makefile`: build.
- `src/minishell.c`: entrypoint.
- `scripts/`: scripts de prueba.

## Documentación
- Flujo de señales: `docs/signals_flow.md`
- Flujo de heredoc: `docs/heredoc_flow.md`
- Checklist de evaluación: `docs/evaluation_checklist.md`
- README de módulo Execute: `src/execute/README.md`
- README de módulo Redir: `src/redir/README.md`

