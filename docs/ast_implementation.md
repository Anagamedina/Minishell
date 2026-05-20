# Implementación de mi Constructor AST

He dado el siguiente paso lógico: transformar mi lista plana de tokens en la estructura jerárquica del **AST**. He implementado la lógica principal en `src/ast/ast_builder.c`, enfocándome en la recursividad y la prioridad de los operadores.

## Cómo he estructurado la construcción

Para que el árbol sea correcto, estoy siguiendo una estrategia de "fuera hacia adentro" basada en la prioridad:

### 1. La búsqueda del Pipe (Prioridad Mínima)
He creado la función `find_last_pipe`. ¿Por qué el último? Porque en un pipeline como `A | B | C`, el último pipe es el que une `(A | B)` con `C`. Al convertir este último pipe en la raíz, aseguro que la ejecución fluya correctamente de izquierda a derecha.

### 2. Segmentación de Comandos
Cuando no hay pipes, entra en juego `parse_command_segment`. Aquí es donde gestiono la relación entre un comando y sus redirecciones. 
- He decidido que las **redirecciones siempre envuelvan al comando**. 
- Si tengo `ls > file`, el nodo raíz de ese segmento será `NODE_REDIRECT`, y su hijo izquierdo será el `NODE_COMMAND` (`ls`). Esto facilita mucho la apertura de archivos antes de ejecutar el comando.

### 3. Extracción de Argumentos
He implementado `extract_command_args` para limpiar la basura del segmento. Esta función ignora los tokens de redirección y sus archivos, extrayendo solo el comando y sus parámetros en una matriz `char **` limpia, lista para ser pasada a `execve` o a mis built-ins.

## Cambios en la infraestructura

Para que todo esto funcione, he realizado los siguientes ajustes:
- **`Makefile`**: He añadido `ast_builder.c` para que se compile con el resto del proyecto.
- **`prototype.h`**: He registrado `build_ast` como la entrada principal de mi nuevo parser.

## El desafío de la recursividad en C98
Implementar esto en C98 con `t_list` es un reto porque no quiero duplicar memoria innecesariamente. Mi siguiente paso será perfeccionar la función `build_ast` para que pueda "cortar" la lista de tokens en sub-listas de forma eficiente sin perder punteros ni causar leaks.

Con esta lógica, mi Minishell ya no solo "lee" comandos, sino que "entiende" la jerarquía de lo que el usuario quiere ejecutar.
