FUNCIONES :
1) Buscar lso operadores de redireccion y capturar los archivos asociados 
2) Abrir los archivossegun el operador: oPEN() •	O_RDONLY para <.
   •	O_WRONLY | O_CREAT | O_TRUNC para >.
   •	O_WRONLY | O_CREAT | O_APPEND para >>.
3) Redirigir la entrada/salida
Usar dup2()
   Para <: Redirigir el archivo al descriptor STDIN_FILENO.
   •	Para >: Redirigir el descriptor STDOUT_FILENO al archivo.
   •	Para 2>: Redirigir el descriptor STDERR_FILENO al archivo.
4) ejecutar el comando


TENER EN CUENTA:
1.	Errores al Abrir Archivos:
•	Verifica si open() falla (retorna -1) y maneja los errores adecuadamente.
2.	Orden de las Redirecciones:
•	En comandos complejos, los operadores pueden mezclarse. Analiza correctamente la prioridad.
3.	Tokens Eliminados:
•	Remueve los operadores y nombres de archivo del array de argumentos antes de llamar a execvp().
4.	Compatibilidad con Pipes:
•	Redirecciones y pipes pueden coexistir. Asegúrate de que dup2() se use de manera adecuada para evitar conflictos entre pipes y redirecciones.
5.	Cierre de Descriptores:
•	Siempre cierra los descriptores de archivo una vez que se han redirigido.
6.	Modo Interactivo:
•	Implementa un bucle para procesar múltiples comandos y manejar redirecciones en cada uno.
      
¿Cómo Manejar Pipes y Redirecciones en tu Proyecto?
•	Identifica las pipes (|) y redirecciones (<, >, >>).
•	Divide el comando en “segmentos” por cada |.
cat < input.txt | grep "pattern" > output.txt
Segmentos:
•	cat < input.txt
•	grep "pattern" > output.txt