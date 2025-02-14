# Proyecto Minishell

**Desarrollado por Ana Medina Burgos y Darunny Salazar**

![Minishell Banner](assets/header.png)

El proyecto **Minishell** busca crear un shell funcional que interprete y ejecute comandos de manera similar a Bash, cumpliendo con los requisitos fundamentales de la Academia 42.

## Objetivo
El shell deberá ofrecer una experiencia interactiva, soportar funcionalidades esenciales de redirección y pipelines, y gestionar variables y señales, todo con un enfoque en la eficiencia y la gestión de memoria.

## Funcionalidades

### Interfaz de Usuario
- Muestra una entrada mientras espera comandos.
- Mantiene un historial funcional para recordar comandos anteriores.

### Ejecución de Comandos
- Localiza y ejecuta comandos usando `PATH` o rutas relativas y absolutas.
- Implementa redirecciones:
  - Entrada (`<`)
  - Salida (`>`, `>>`)
  - Heredoc (`<<`)
- Soporta pipelines (`|`) para conectar comandos en una cadena.

### Variables y Entorno
- Expande variables de entorno (`$` y `$?`).
- Gestiona comillas simples y dobles, respetando reglas para metacaracteres.

### Control de Señales
- Gestiona señales `ctrl-C`, `ctrl-D`, y `ctrl-\` como en Bash, con efectos específicos para el modo interactivo.
- Usa una sola variable global para almacenar el número de señal.

### Built-ins
El shell incluye los comandos internos esenciales:
  - `echo` con opción `-n`
  - `cd` para cambio de directorio
  - `pwd` para mostrar el directorio actual
  - `export` para manejar variables de entorno
  - `unset` para eliminar variables de entorno
  - `env` para mostrar las variables de entorno
  - `exit` para salir del shell

## Requerimientos Técnicos
- Uso de la biblioteca `libft` y funciones específicas autorizadas.
- Gestión de memoria para evitar leaks (excepto en `readline`, según especificaciones).

## Estructura del Proyecto
El proyecto cuenta con un **Makefile** para facilitar la compilación, y cada funcionalidad está organizada en archivos `.h` y `.c` que garantizan una estructura clara y modular.

Aquí tienes la sección organizada para tu **README** con un formato claro y estructurado:

---

## 📌 **Notas Importantes & Comandos Útiles**

### 🔹 **Ejecutar Bash sin variables de entorno ni configuraciones**

``` plaintext 
env -i bash --noprofile --norc
```

**¿Qué hace este comando?**  
Ejecuta **Bash en un entorno limpio**, sin cargar configuraciones ni heredar variables del entorno actual.

#### **📌 Desglose del comando:**
- **`env -i`** (`--ignore-environment`)
    - Inicia un nuevo entorno **vacío**, sin heredar variables como `PATH`, `HOME`, `USER`.
    - Útil para pruebas o depuración sin configuraciones heredadas.

- **`bash --noprofile --norc`**
    - **`--noprofile`** → No carga `~/.bash_profile`, `~/.bash_login` ni `/etc/profile`.
    - **`--norc`** → No ejecuta `~/.bashrc`, evitando configuraciones personalizadas.

### **📌 Ejemplo de uso**

Para verificar que el entorno realmente está vacío, ejecuta:

```sh
  env -i bash --noprofile --norc
  env
```

**Salida esperada:** (Sin variables de entorno cargadas)
```sh
  # No muestra ninguna variable de entorno
```

---

## VARIABLES DE ENTORNO A INICIALIZAR

### **📌 Configuración del Entorno en Minishell**

Esta sección describe las **variables de entorno** que se inicializan si no existen al ejecutar **Minishell**, basándonos en nuestra función `configure_shell_env()`.

---

## **🔹 Variables de entorno inicializadas**
Minishell verifica y crea las siguientes variables si no existen en el entorno:

| **Variable** | **Propósito** | **Valor predeterminado si no existe** |
|-------------|--------------|----------------------------------------|
| `OLDPWD` | Guarda el directorio anterior para `cd -` | `""` (vacío hasta que `cd` lo modifique) |
| `PATH` | Define los directorios donde buscar comandos ejecutables | `"/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin"` |
| `HOME` | Directorio home del usuario | Valor de `getenv("HOME")` o `"/home/"` si no existe |
| `USER` | Nombre del usuario actual | `getenv("USER")` o `"unknown"` si no existe |
| `SHLVL` | Nivel del shell, aumenta con cada nueva instancia | Si `SHLVL >= 100`, se reinicia a `"1"` |

---

## **🔹 Manejo especial de `OLDPWD` y `PWD`**
### **¿Debe `OLDPWD` reiniciarse a `""` o mantenerse?**
Si `OLDPWD` ya existe con una ruta válida, **se deja intacto**.  
Si `OLDPWD` no existe, **se inicializa en `""` (vacío)** hasta que `cd` lo actualice.

### **¿Cómo afecta `PWD`?**
- `PWD` **se mantiene como está** porque representa el directorio actual.
- Bash también lo mantiene si existe en `env`.

---

## **🔹 Manejo de `SHLVL`**
1. Si `SHLVL` **no existe o es negativo**, se inicializa en `0`.
2. Si `SHLVL >= 100`, **se muestra una advertencia y se reinicia a `1`**.
3. En otros casos, **se incrementa en `+1`**.

Ejemplo de mensaje de advertencia si `SHLVL >= 100`:
```sh
mish: warning: shell level (100) too high, resetting to 1
```

---

## **📌 ¿Cómo se comporta esto en Bash?**
Ejecutando **Bash en un entorno vacío** (`env -i bash --noprofile --norc`), obtenemos:
```sh
PWD=/home/user
SHLVL=1
_=/usr/bin/env
```
➡️ **Minishell replica este comportamiento, asegurando compatibilidad.**

---

🚀 **Con esta implementación, Minishell maneja el entorno de forma eficiente y compatible con Bash.**

---


**Esperamos que este shell se convierta en una herramienta eficaz y amigable para interactuar con el sistema.**

¡Gracias por revisar nuestro proyecto y no dudes en contactarnos para cualquier pregunta o sugerencia!
