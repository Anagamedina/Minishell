# Ejecución del AST: El Motor de mi Minishell

He implementado el motor de ejecución basado en el **AST** en `src/ast/ast_executor.c`. Este componente es el que realmente "da vida" a los comandos, recorriendo el árbol de forma recursiva y gestionando los procesos y descriptores de archivos.

## Mi Lógica de Ejecución

La ejecución se basa en un recorrido recursivo del árbol. Dependiendo del tipo de nodo, realizo una acción diferente:

### 1. Nodos PIPE (`|`)
Es el corazón de la multitarea. 
- Utilizo `pipe()` para crear un canal de comunicación.
- Hago dos `fork()` (uno para el hijo izquierdo y otro para el derecho).
- El hijo izquierdo redirige su salida estándar al pipe.
- El hijo derecho redirige su entrada estándar desde el pipe.
- El padre espera a que ambos terminen, capturando el estado de salida del último comando.

### 2. Nodos REDIRECT (`<`, `>`, `>>`)
Aquí es donde gestiono los archivos.
- Abro el archivo con los flags correctos (`O_CREAT`, `O_APPEND`, `O_TRUNC`, etc.).
- Utilizo `dup2()` para redirigir `STDIN` o `STDOUT`.
- Ejecuto recursivamente el subárbol izquierdo (que contiene el comando).
- **Importante**: Restauro los descriptores originales después de la ejecución para que la shell siga funcionando correctamente.

### 3. Nodos COMMAND
Es el nodo hoja, donde termina la recursión.
- Aquí es donde se produce la ejecución real.
- Compruebo si es un **Built-in** (como `cd` o `export`) o un comando externo.
- Si es externo, llamo a `execve` a través de mis funciones de utilidad existentes.

## Ventajas de este Enfoque

1.  **Aislamiento**: Cada parte del pipeline se ejecuta en su propio contexto, evitando que un error en un comando corrompa toda la shell.
2.  **Recursividad Limpia**: La lógica de `execute_ast(node->left)` permite manejar estructuras complejas como `cat file | grep "hola" > out` de forma natural.
3.  **Gestión de FDs**: Al usar la pila de recursión, la apertura y cierre de descriptores de archivos es mucho más fácil de seguir y depurar.

Con este motor, mi Minishell ha pasado de ser un simple intérprete de líneas a un sistema de ejecución jerárquico y profesional.
