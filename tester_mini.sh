#!/bin/bash

# Nombre del ejecutable de minishell
MINISHELL_EXEC=./minishell

# Archivo temporal para guardar la salida de minishell
TEMP_OUTPUT=temp_minishell_output.txt

# Comandos de prueba
COMMANDS=(
    "echo Hello, World!"
    "echo \$PWD"
    "ls"
)

# Salidas esperadas (puedes personalizarlas)
EXPECTED_OUTPUTS=(
    "minishell> echo Hello, World!"
    "minishell> $PWD"
    "minishell> $(ls)"
)

# Colores para los mensajes
GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

# Verifica si el ejecutable existe
if [[ ! -f "$MINISHELL_EXEC" ]]; then
    echo -e "${RED}Error: No se encontró el ejecutable $MINISHELL_EXEC.${RESET}"
    exit 1
fi

# Inicia pruebas
echo "Iniciando pruebas para $MINISHELL_EXEC..."
for i in "${!COMMANDS[@]}"; do
    COMMAND="${COMMANDS[$i]}"
    EXPECTED="${EXPECTED_OUTPUTS[$i]}"

    echo "Probando comando: $COMMAND"

    # Ejecuta el comando en minishell y captura la salida
    printf "$COMMAND\nexit\n" | $MINISHELL_EXEC > $TEMP_OUTPUT 2>&1

    # Captura la salida real
    ACTUAL_OUTPUT=$(cat $TEMP_OUTPUT | grep -v "minishell>" | head -n 1)

    # Compara la salida
    if [[ "$ACTUAL_OUTPUT" == "$EXPECTED" ]]; then
        echo -e "${GREEN}[OK]${RESET} Comando: $COMMAND"
    else
        echo -e "${RED}[FAIL]${RESET} Comando: $COMMAND"
        echo -e "${RED}Esperado:${RESET} $EXPECTED"
        echo -e "${RED}Obtenido:${RESET} $ACTUAL_OUTPUT"
    fi

done

# Limpieza
echo "Limpiando archivos temporales..."
rm -f $TEMP_OUTPUT

echo "Pruebas finalizadas."
