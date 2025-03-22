#!/bin/bash

# Nombre del ejecutable de minishell
MINISHELL_EXEC=./minishell

# Archivo temporal para capturar la salida de minishell
TEMP_OUTPUT=temp_builtins_output.txt

# Comandos de prueba para builtins
COMMANDS=(
    "echo Hola Mundo"                     # echo simple
    "echo \"Hola \$USER\""                 # echo con variable de entorno
)

# Salidas esperadas según el comportamiento de Bash
EXPECTED_OUTPUTS=(
    "Hola Mundo"
    "Hola $(echo $USER)"
)

# Colores para los mensajes
GREEN="\033[0;32m"
RED="\033[0;31m"
RESET="\033[0m"

# Verifica si minishell existe
if [[ ! -f "$MINISHELL_EXEC" ]]; then
    echo "❌ Error: No se encontró $MINISHELL_EXEC."
    exit 1
fi

echo "🔍 Iniciando pruebas para $MINISHELL_EXEC..."

# Ejecutar cada prueba
for i in "${!COMMANDS[@]}"; do
    TEST_CMD="${COMMANDS[$i]}"
    EXPECTED="${EXPECTED_OUTPUTS[$i]}"

    echo "▶️ Ejecutando: $TEST_CMD"

    # Ejecutar comando en minishell y capturar salida
    echo -e "$TEST_CMD\nexit" | $MINISHELL_EXEC > $TEMP_OUTPUT 2>&1

    # Obtener salida real
    ACTUAL_OUTPUT=$(grep -v "minishell>" $TEMP_OUTPUT | head -n 1)

    # Comparar salida con resultado esperado
    if [[ "$ACTUAL_OUTPUT" == "$EXPECTED" ]]; then
        echo "✅ [OK]: $TEST_CMD"
    else
        echo "❌ [FAIL]: $TEST_CMD"
        echo "   🔹 Esperado: '$EXPECTED'"
        echo "   🔹 Obtenido: '$ACTUAL_OUTPUT'"
    fi
done

# Limpieza
rm -f $TEMP_OUTPUT
echo "🏁 Pruebas finalizadas."