# Apuntes Técnicos: Implementación de Utilidades y Constructor del AST

He completado la fase de codificación de las herramientas base para mi nuevo sistema de AST. Aquí detallo exactamente qué he hecho y cómo he estructurado el código para que sea escalable y seguro.

## 1. Organización del Código
He creado una nueva carpeta `src/ast/` para separar la lógica del árbol del resto del parser. Esto mantiene el proyecto limpio y facilita la depuración.

## 2. Las Herramientas Base (`ast_utils.c`)
He implementado las funciones que me permiten "fabricar" las piezas de mi árbol:

*   **`create_ast_node`**: Es mi constructor genérico. Me asegura que cada vez que pido un nodo, este nazca con sus punteros a `NULL` y un estado limpio, evitando comportamientos erráticos por memoria basura.
*   **`create_pipe_node`**: Esta función es la que "cose" dos subárboles. Recibe dos nodos (izquierdo y derecho) y los une bajo un nodo padre de tipo PIPE.
*   **`create_redir_node`**: Aquí gestiono la entrada/salida. El nodo guarda el tipo de redirección y el nombre del archivo, y vincula el comando afectado a su rama izquierda.
*   **`free_ast`**: Mi seguro de vida contra los **Memory Leaks**. Al ser recursiva, me permite liberar estructuras increíblemente complejas con una sola llamada, asegurando que cada `char **` y cada `char *` se limpie en el orden correcto (Post-orden).

## 3. El Cerebro del Árbol (`ast_builder.c`)
He empezado a implementar la lógica que decide la forma del árbol:

*   **Prioridad de Operadores**: He programado `find_last_pipe` para que el árbol se construya respetando que el Pipe es lo último en ejecutarse, quedando así en la raíz.
*   **Extracción Limpia**: Con `extract_command_args`, me aseguro de que los nodos de comando solo contengan lo que realmente necesitan (comando + flags), filtrando las redirecciones que ya han sido procesadas.

## 4. Integración en la Shell
Para que todo esto no sea solo código muerto, he realizado cambios en la infraestructura del proyecto:

*   **Cabeceras**: He actualizado `minishell.h` con los nuevos tipos de datos y `prototype.h` con las funciones para que cualquier parte del programa pueda interactuar con el AST.
*   **Compilación**: He modificado el `Makefile` para incluir estos nuevos archivos. Ahora, al hacer `make`, el motor del AST se compila automáticamente como parte del núcleo de Minishell.

Este cambio marca el fin de mi dependencia de las listas secuenciales y abre la puerta a una ejecución mucho más potente y profesional.
