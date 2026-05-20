# Resumen de Correcciones de Errores Críticos

En esta revisión se han solucionado varios problemas que causaban inestabilidad y comportamientos incorrectos en Minishell.

## 1. Segmentation Faults (Segfaults)

### Doble Liberación (Double Free)
- **Archivo**: `src/expand/expand_vars.c`
- **Problema**: La función `process_split_words` liberaba un puntero que ya había sido liberado dentro de `replace_env_var_in_token`.
- **Solución**: Se eliminó la llamada redundante a `free(tmp)`.

### Desreferencia de NULL
- **Archivo**: `src/expand/expand_token_utils.c`
- **Problema**: `get_and_reconstruct_token` no verificaba si el valor de una variable de entorno era NULL antes de usar `ft_strlen`.
- **Solución**: Se añadieron comprobaciones de seguridad para manejar variables inexistentes.

## 2. Gestión de Memoria y Leaks

### Comando `export`
- **Problema**: Fugas de memoria al actualizar variables existentes y manejo inconsistente de punteros en el caso de concatenación (`+=`).
- **Solución**: Se refactorizó `update_env_var` y `add_or_update_env_variable` para clarificar la propiedad de la memoria y asegurar que todos los temporales se liberen.

### Matriz de Entorno (`envp_to_array`)
- **Problema**: `free_env_array` tenía un error de índice que provocaba accesos inválidos y fugas.
- **Solución**: Se corrigió el bucle de liberación para cubrir todos los elementos correctamente.
