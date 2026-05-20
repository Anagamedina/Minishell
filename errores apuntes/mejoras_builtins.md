# Mejoras en Comandos Built-in

Se han ajustado los comandos internos para que su comportamiento sea idéntico al de Bash y gestionen correctamente el estado de la shell.

## 1. Comando `exit`
- **Cambio**: Ahora maneja correctamente múltiples argumentos.
- **Comportamiento**: 
  - `exit 1 2` -> Imprime error "too many arguments" y **no sale**.
  - `exit abc` -> Imprime error "numeric argument required" y **sale** con código 2.
  - `exit 42` -> Sale con código 42.

## 2. Comando `unset`
- **Validación**: Ahora usa `is_valid_identifier` para rechazar nombres inválidos (ej. `unset 123VAR`).
- **Sincronización**: Si se elimina `PATH`, se regenera la matriz de entorno para que los cambios afecten inmediatamente a la búsqueda de comandos externos.

## 3. Comando `export`
- **Sin argumentos**: Ahora imprime la lista de variables con el formato `declare -x`.
- **Validación**: Mejora en la detección de sintaxis inválida.

## 4. Estado de Salida (`$?`)
- **Cambio**: Todos los built-ins (`echo`, `cd`, `pwd`, `env`, `export`, `unset`) ahora actualizan `mini->exit_status`.
- **Importancia**: Esto permite que el usuario pueda verificar si el comando tuvo éxito usando `echo $?`.
