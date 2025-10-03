### Evaluation Points Guide

Guía específica para los puntos de evaluación del sujeto de Minishell.

#### 1. `env` - Mostrar variables de entorno

**Objetivo**: Verificar que `env` muestra las variables de entorno actuales.

**Tests**:
```bash
# Básico - mostrar todas las variables
env

# Filtrar variables específicas
env | grep PATH
env | grep HOME
env | grep USER
env | grep PWD

# Verificar formato (clave=valor)
env | head -5

# Comparar con bash
env > minishell_env.txt
bash -c "env" > bash_env.txt
diff minishell_env.txt bash_env.txt
```

**Resultado esperado**: Lista de variables en formato `KEY=value`, similar a bash.

---

#### 2. `export` - Crear y modificar variables

**Objetivo**: Crear nuevas variables, modificar existentes y verificar con `env`.

**Tests**:
```bash
# Crear nueva variable
export NEWVAR=hello
env | grep NEWVAR

# Modificar variable existente
export PATH=/new/path
env | grep PATH

# Crear múltiples variables
export VAR1=1 VAR2=2 VAR3=3
env | grep VAR

# Crear variable sin valor
export EMPTYVAR=
env | grep EMPTYVAR

# Crear variable con espacios
export SPACES="hello world"
env | grep SPACES

# Verificar que aparece en env después de export
export TESTVAR=test
env | grep TESTVAR
```

**Resultado esperado**: Las variables exportadas aparecen en `env` y pueden ser usadas.

---

#### 3. `unset` - Eliminar variables

**Objetivo**: Eliminar variables y verificar que desaparecen de `env`.

**Tests**:
```bash
# Crear variables para eliminar
export VAR1=1 VAR2=2 VAR3=3
env | grep VAR

# Eliminar una variable
unset VAR1
env | grep VAR1    # no debería aparecer

# Eliminar múltiples variables
unset VAR2 VAR3
env | grep VAR     # no debería aparecer ninguna

# Eliminar variable inexistente (no debería dar error)
unset NOEXISTE

# Crear, mostrar, eliminar, verificar
export TEMPVAR=temp
env | grep TEMPVAR
unset TEMPVAR
env | grep TEMPVAR    # no debería aparecer
```

**Resultado esperado**: Las variables unset desaparecen de `env`.

---

#### 4. `cd` - Cambiar directorio

**Objetivo**: Moverse entre directorios y verificar con `/bin/ls`.

**Tests**:
```bash
# cd básico
cd /tmp
/bin/ls

# cd a home
cd ~
/bin/ls

# cd a directorio relativo
cd /tmp
mkdir test_dir
cd test_dir
/bin/ls

# cd con '.'
cd .
/bin/ls

# cd con '..'
cd ..
/bin/ls

# cd con múltiples '..'
cd ../..
/bin/ls

# cd a directorio inexistente
cd /noexiste    # error esperado
/bin/ls         # debería estar en el mismo directorio

# cd sin argumentos (debería ir a home)
cd /tmp
cd
/bin/ls

# cd con argumentos múltiples
cd /tmp /home   # error esperado
/bin/ls

# Secuencia de cd's
cd /
/bin/ls
cd tmp
/bin/ls
cd ..
/bin/ls
cd ~
/bin/ls
```

**Resultado esperado**: `cd` cambia el directorio y `/bin/ls` muestra el contenido correcto.

---

#### 5. `pwd` - Directorio actual

**Objetivo**: Mostrar el directorio de trabajo actual.

**Tests**:
```bash
# pwd básico
pwd

# pwd en diferentes directorios
cd /tmp
pwd

cd ~
pwd

cd /
pwd

cd /usr/bin
pwd

# pwd después de cd relativo
cd /tmp
mkdir test_pwd
cd test_pwd
pwd

cd ..
pwd

# pwd con redirección
pwd > pwd_output.txt
cat pwd_output.txt

# Verificar que pwd es consistente
CURRENT_DIR=$(pwd)
echo "Current dir: $CURRENT_DIR"
```

**Resultado esperado**: `pwd` muestra la ruta absoluta del directorio actual.

---

#### 6. Rutas relativas - Comandos con rutas relativas

**Objetivo**: Ejecutar comandos usando rutas relativas complejas.

**Tests**:
```bash
# Crear estructura de directorios
mkdir -p test/level1/level2/level3
cd test/level1/level2/level3

# Comandos con rutas relativas simples
../../../../bin/ls
../../../bin/pwd

# Comandos con rutas relativas complejas
../../../../bin/echo "hello from deep directory"
../../../bin/cat /etc/passwd | ../../../../bin/head -3

# Navegar con rutas relativas
cd ../../..
/bin/ls

cd level1/level2
/bin/ls

cd ../../../..
/bin/ls

# Limpiar
rm -rf test
```

**Resultado esperado**: Los comandos funcionan correctamente con rutas relativas.

---

#### 7. PATH del entorno - Comandos sin ruta

**Objetivo**: Ejecutar comandos usando el PATH y verificar el orden de búsqueda.

**Tests**:
```bash
# Comandos básicos sin ruta
ls
pwd
echo "test"
wc -l /etc/passwd
awk '{print $1}' /etc/passwd | head -3

# Verificar PATH actual
echo $PATH

# Crear directorio temporal con comando personalizado
mkdir -p /tmp/test_path
echo '#!/bin/sh\necho "Custom command from /tmp/test_path"' > /tmp/test_path/ls
chmod +x /tmp/test_path/ls

# Agregar al PATH (al final)
export PATH=$PATH:/tmp/test_path
which ls
ls    # debería usar el ls normal, no el personalizado

# Agregar al PATH (al principio)
export PATH=/tmp/test_path:$PATH
which ls
ls    # debería usar el ls personalizado

# Verificar orden de búsqueda (directorio1:directorio2:directorio3)
# Crear múltiples directorios con comandos diferentes
mkdir -p /tmp/path1 /tmp/path2 /tmp/path3

# Crear comando 'testcmd' en cada directorio con contenido diferente
echo '#!/bin/sh\necho "Command from path1"' > /tmp/path1/testcmd
echo '#!/bin/sh\necho "Command from path2"' > /tmp/path2/testcmd  
echo '#!/bin/sh\necho "Command from path3"' > /tmp/path3/testcmd

# Hacer ejecutables
chmod +x /tmp/path1/testcmd /tmp/path2/testcmd /tmp/path3/testcmd

# Test 1: path1:path2:path3 (debería usar path1)
export PATH="/tmp/path1:/tmp/path2:/tmp/path3"
which testcmd    # debería mostrar /tmp/path1/testcmd
testcmd          # debería mostrar "Command from path1"

# Test 2: path2:path1:path3 (debería usar path2)
export PATH="/tmp/path2:/tmp/path1:/tmp/path3"
which testcmd    # debería mostrar /tmp/path2/testcmd
testcmd          # debería mostrar "Command from path2"

# Test 3: path3:path2:path1 (debería usar path3)
export PATH="/tmp/path3:/tmp/path2:/tmp/path1"
which testcmd    # debería mostrar /tmp/path3/testcmd
testcmd          # debería mostrar "Command from path3"

# Test 4: Verificar que si el primer directorio no tiene el comando, busca el segundo
rm /tmp/path1/testcmd  # eliminar comando del primer directorio
export PATH="/tmp/path1:/tmp/path2:/tmp/path3"
which testcmd    # debería mostrar /tmp/path2/testcmd
testcmd          # debería mostrar "Command from path2"

# Test 5: Verificar que si los primeros directorios no existen, busca en los siguientes
export PATH="/noexiste1:/noexiste2:/tmp/path3"
which testcmd    # debería mostrar /tmp/path3/testcmd
testcmd          # debería mostrar "Command from path3"

# Test 6: Verificar con comando real (ls)
# Crear ls personalizado en path1
echo '#!/bin/sh\necho "Custom ls from path1"' > /tmp/path1/ls
chmod +x /tmp/path1/ls

export PATH="/tmp/path1:/usr/bin:/bin"
which ls         # debería mostrar /tmp/path1/ls
ls               # debería mostrar "Custom ls from path1"

# Limpiar
rm -rf /tmp/path1 /tmp/path2 /tmp/path3

# Unset PATH y verificar que comandos no funcionan
unset PATH
ls    # error: command not found
pwd   # error: command not found

# Restaurar PATH
export PATH="/usr/bin:/bin:/usr/sbin:/sbin"
ls    # debería funcionar de nuevo

# Limpiar
rm -rf /tmp/test_path
```

**Resultado esperado**: 
- Comandos funcionan con PATH normal
- PATH se busca de izquierda a derecha
- Sin PATH, comandos fallan
- Con PATH personalizado, se usa el comando del directorio correcto

---

#### 8. Tests de integración

**Tests combinados**:
```bash
# Secuencia completa
pwd
cd /tmp
pwd
export TESTVAR=hello
env | grep TESTVAR
unset TESTVAR
env | grep TESTVAR
ls
cd ~
pwd
```

**Resultado esperado**: Todos los comandos funcionan correctamente en secuencia.

---

#### 9. Casos edge

**Tests adicionales**:
```bash
# Variables con caracteres especiales
export VAR_WITH_UNDERSCORE=test
export VAR-WITH-DASH=test    # error esperado
export 1VAR=test             # error esperado

# PATH con directorios inexistentes
export PATH="/noexiste:/usr/bin:/bin"
ls    # debería funcionar (busca en /usr/bin)

# PATH vacío
export PATH=""
ls    # error: command not found

# cd con string vacío
cd ""
pwd   # debería ir a home

# cd con solo espacios
cd "   "
pwd   # error esperado
```

**Resultado esperado**: Comportamiento consistente con bash para casos edge.
