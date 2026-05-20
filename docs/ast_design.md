# Rediseño de mi Minishell: El Desafío del AST

He decidido dar un giro radical a la arquitectura de mi Minishell. Después de lidiar con constantes **Segmentation Faults** y fugas de memoria en mi antiguo parser secuencial, me he dado cuenta de que intentar gestionar pipes y redirecciones como una simple lista es una receta para el desastre. Aunque el proyecto 42 no nos exige operadores lógicos complejos, he optado por implementar un **Árbol de Sintaxis Abstracta (AST)** para garantizar una robustez absoluta.

## El Problema Técnico que estoy solucionando

Mi parser anterior intentaba leer los comandos de forma lineal. Esto funcionaba bien para comandos simples, pero en cuanto introducía pipelines complejos como `cat file | grep "hola" > output.txt`, la lógica de "quién es hijo de quién" se volvía extremadamente frágil. 

Los problemas principales que estoy atacando son:
1.  **Fragilidad en la ejecución**: Gestionar los descriptores de archivos (FDs) en una lista secuencial es propenso a errores. Con un AST, la jerarquía de ejecución está implícita en la estructura del árbol.
2.  **Fugas de memoria (Leaks)**: Si un comando fallaba en mitad de una secuencia, liberar todos los recursos era una pesadilla. Un árbol me permite usar recursividad para limpiar todo de forma sistemática.
3.  **Expansión de variables ($)**: Expandir variables antes de conocer la estructura final del comando causaba que el parseo se rompiera. Con el AST, primero defino la estructura y luego expando los datos.

## Mi Diseño de Estructura (C98)

He diseñado una estructura de nodo versátil que puede representar cualquier operación en mi shell, cumpliendo estrictamente con el estándar C98.

```c
typedef enum e_ast_type
{
    NODE_PIPE,      /* Representa un '|' */
    NODE_REDIRECT,  /* Representa <, >, >> o << */
    NODE_COMMAND    /* Representa un comando y sus argumentos */
} t_ast_type;

typedef struct s_ast_node
{
    t_ast_type          type;
    char                **args;         /* Solo para NODE_COMMAND */
    int                 redir_type;     /* Solo para NODE_REDIRECT */
    char                *file;          /* Nombre del archivo o delimitador */
    struct s_ast_node   *left;          /* Rama izquierda */
    struct s_ast_node   *right;         /* Rama derecha */
} t_ast_node;
```

## Mi Algoritmo de Construcción

Para construir el árbol, estoy aplicando una lógica de **prioridad inversa**. Busco el operador con menos prioridad (el Pipe) para que se convierta en la raíz.

1.  **Busco el último Pipe**: Escaneo los tokens. Si encuentro un `|`, lo convierto en el nodo padre. Todo lo que está a su izquierda va a la rama `left` y lo que está a la derecha a la rama `right`.
2.  **Gestiono las Redirecciones**: Si no hay pipes, busco redirecciones. El nodo de redirección guardará el archivo en una rama y el comando que está siendo redireccionado en la otra.
3.  **Nodos Hoja**: Cuando ya no quedan operadores, lo que tengo es un comando simple con sus argumentos, que guardo en un `NODE_COMMAND`.

### Ejemplo de mi nueva jerarquía: `ls -l | wc -l > out`

```text
          [NODE_PIPE]
         /           \
   [COMMAND]       [REDIRECT (>)]
   (ls -l)         /           \
               [COMMAND]      (out)
               (wc -l)
```

## Gestión de Memoria y Recursividad

Esta es la parte que más me entusiasma. He implementado una función de liberación recursiva que me asegura **cero leaks**. Al ser un árbol, simplemente tengo que bajar hasta las hojas y empezar a liberar hacia arriba (Post-orden).

```c
void free_ast(t_ast_node *node)
{
    if (!node)
        return;
    free_ast(node->left);
    free_ast(node->right);
    
    if (node->type == NODE_COMMAND && node->args)
        free_string_matrix(node->args);
    if (node->type == NODE_REDIRECT && node->file)
        free(node->file);
    free(node);
}
```

Con este cambio, mi Minishell no solo será más estable, sino que su mantenimiento y escalabilidad serán mucho más sencillos. He pasado de un sistema que "intentaba adivinar" qué hacer, a uno que tiene una representación matemática clara de la intención del usuario.
