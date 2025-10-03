### Builtins Test Guide

Guía específica para testear todos los builtins de Minishell.

#### `echo`
```bash
# Básico
echo hello
echo hello world
echo "hello world"
echo 'hello world'

# Flag -n (sin salto de línea)
echo -n hello
echo -n hello world
echo -n "hello world"
echo -n 'hello world'

# Casos especiales
echo -n -n hello    # múltiples -n
echo -n -e hello    # -n con otra flag
echo -n             # solo -n
echo ""             # string vacío
echo ' '            # solo espacio
echo "hello\nworld" # con \n literal

# Variables
export VAR=test
echo $VAR
echo "$VAR"
echo '$VAR'
```

#### `pwd`
```bash
# Básico
pwd

# En diferentes directorios
cd /tmp
pwd
cd ~
pwd
cd /
pwd

# Con redirección
pwd > pwd_output.txt
cat pwd_output.txt
```

#### `cd`
```bash
# Directorio home
cd
pwd

# Directorio absoluto
cd /tmp
pwd

# Directorio relativo
cd ..
pwd

# Directorio inexistente
cd /noexiste    # error: No such file or directory

# Sin permisos
cd /root        # error: Permission denied

# cd - (directorio anterior)
cd /tmp
cd ~
cd -
pwd             # debería mostrar /tmp

# cd con argumentos múltiples
cd /tmp /home   # error: too many arguments

# cd con string vacío
cd ""           # debería ir a home

# cd con solo espacios
cd "   "        # error: No such file or directory
```

#### `export`
```bash
# Mostrar variables exportadas
export

# Exportar nueva variable
export NEWVAR=hello
echo $NEWVAR
export

# Exportar variable existente (modificar)
export PATH=/new/path
echo $PATH

# Exportar sin valor
export EMPTYVAR=
echo $EMPTYVAR

# Exportar con espacios en el valor
export SPACES="hello world"
echo "$SPACES"

# Exportar múltiples variables
export VAR1=1 VAR2=2 VAR3=3
echo $VAR1 $VAR2 $VAR3

# Exportar variable con caracteres especiales
export SPECIAL="hello\$world"
echo "$SPECIAL"

# Exportar variable que empieza con número
export 1VAR=test    # error: not a valid identifier

# Exportar variable con caracteres inválidos
export VAR-NAME=test    # error: not a valid identifier

# Exportar solo el nombre
export VARNAME         # sin valor, se exporta como vacía
```

#### `unset`
```bash
# Unset variable existente
export TESTVAR=hello
echo $TESTVAR
unset TESTVAR
echo $TESTVAR         # debería estar vacía

# Unset variable inexistente
unset NOEXISTE        # no debería dar error

# Unset múltiples variables
export VAR1=1 VAR2=2 VAR3=3
unset VAR1 VAR2 VAR3
echo $VAR1 $VAR2 $VAR3

# Unset variable de solo lectura
unset PATH            # debería funcionar en minishell
unset HOME            # debería funcionar en minishell

# Unset con nombre inválido
unset 1VAR            # error: not a valid identifier
unset VAR-NAME        # error: not a valid identifier
```

#### `env`
```bash
# Mostrar todas las variables de entorno
env

# Filtrar variables específicas
env | grep PATH
env | grep HOME
env | grep USER

# Verificar que muestra variables exportadas
export NEWVAR=test
env | grep NEWVAR

# Verificar que no muestra variables unset
export TEMPVAR=temp
unset TEMPVAR
env | grep TEMPVAR    # no debería aparecer
```

#### `exit`
```bash
# Exit con código 0
exit
echo $?               # debería ser 0

# Exit con código específico
exit 42
echo $?               # debería ser 42

# Exit con código 0 explícito
exit 0
echo $?               # debería ser 0

# Exit con código negativo
exit -1
echo $?               # debería ser 255 (normalizado)

# Exit con código > 255
exit 300
echo $?               # debería ser 44 (300 % 256)

# Exit con argumento no numérico
exit abc              # error: numeric argument required
echo $?               # debería ser 2

# Exit con múltiples argumentos
exit 1 2              # error: too many arguments
echo $?               # debería ser 1

# Exit con espacios
exit " 42 "           # debería funcionar (trim spaces)

# Exit con decimales
exit 42.5             # error: numeric argument required
```

#### Combinaciones de Builtins
```bash
# Export y echo
export TEST=hello
echo $TEST

# cd y pwd
cd /tmp
pwd

# Export, unset, env
export VAR1=1 VAR2=2
env | grep VAR
unset VAR1
env | grep VAR

# Pipeline con builtins
echo hello | wc -c
pwd | cat
export | grep PATH

# Redirecciones con builtins
echo hello > output.txt
cat output.txt
pwd > pwd.txt
cat pwd.txt

# Heredoc con builtins
cat << EOF
$(pwd)
$(echo hello)
EOF
```

#### Casos Edge
```bash
# Builtins con argumentos muy largos
echo $(printf 'a%.0s' {1..1000})

# Builtins con caracteres especiales
echo "hello\$world"
echo 'hello$world'
echo "hello\nworld"
echo -e "hello\nworld"    # si implementas -e

# Variables con caracteres especiales
export VAR='hello world'
echo "$VAR"
export VAR="hello\$world"
echo "$VAR"

# Directorios con espacios
mkdir "test dir"
cd "test dir"
pwd
cd ..
rmdir "test dir"
```

#### Verificación de Exit Status
```bash
# Comandos exitosos
echo hello
echo $?               # 0

pwd
echo $?               # 0

cd /tmp
echo $?               # 0

export VAR=test
echo $?               # 0

# Comandos con error
cd /noexiste
echo $?               # 1

export 1VAR=test
echo $?               # 1

exit abc
echo $?               # 2
```
