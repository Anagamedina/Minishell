#!/bin/bash

# Nombre del ejecutable de minishell
MINISHELL_EXEC=./minishell

# Archivo temporal para guardar la salida de minishell
TEMP_OUTPUT=temp_minishell_output.txt

# Comandos de prueba
#    "echo Hello, World!"                     # Caso 1
#    "echo \"Hola 'Mundo'\""                  # Caso 2
#    "echo 'Hola \"Mundo\"'"                  # Caso 3
#    "echo \"Hola & Mundo * \$ ?\""           # Caso 4
#    "echo 'Hola & Mundo * \$ ?'"             # Caso 5
#    "echo \"Hola $USER, esto cuesta $100\"" # Caso 6
#    "echo \"Hola\nMundo\""                   # Caso 7
#    "echo \"Hola \$\nMundo\""                # Caso 8
#    "echo "" \$ \"\" '' \*"             # Caso 9
COMMANDS=(
#    "echo \"Hola \$VAR_INEXISTENTE, cómo estás?\"" # Caso 11
#    "echo \"Hola $USER$HOME\""               # Caso 12
#    "echo \"'Hola' \\\"Mundo\\\" '$USER' \\\"$HOME\\\"\"" # Caso 13
#    "echo \"Hola	Mundo\""                   # Caso 14
#    "echo \"Hola\" '' \"Mundo\" \"\" \"!\""  # Caso 15
)
# Salidas esperadas (personalizadas según el comportamiento esperado de minishell)
#    "[Hello, World!]"                     # Caso 1
#    "[Hola 'Mundo']"                      # Caso 2
#    "[Hola \"Mundo\"]"                    # Caso 3
#    "[Hola & Mundo * $ ?]"                # Caso 4
#    "[Hola & Mundo * \$ ?]"               # Caso 5
#    "[Hola $USER, esto cuesta 00]"     # Caso 6

#    "[HolanMundo]"                       # Caso 7
#    "[Hola $nMundo]"                     # Caso 8
EXPECTED_OUTPUTS=(
#    "[Hola , cómo estás?]"                # Caso 11
#    "[Hola $USER$HOME]"                   # Caso 12
#    "['Hola' \"Mundo\" '$USER' \"$HOME\"]" # Caso 13
#    "[Hola	Mundo]"                       # Caso 14
#    "[Hola Mundo !]"                      # Caso 15
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
