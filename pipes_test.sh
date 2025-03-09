#!/bin/bash

# Ruta de tu minishell (ajustar si es necesario)
MINISHELL=./minishell

echo "===== TEST PIPES EN MINISHELL ====="

# Asegurar que Minishell existe
if [ ! -f "$MINISHELL" ]; then
    echo "❌ Error: Minishell no encontrado en $MINISHELL"
    exit 1
fi

echo "✅ Minishell encontrado. Iniciando pruebas..."

# Ejecuta Minishell en modo batch con pipes
run_test() {
    echo "🔹 Ejecutando prueba: $1"
    echo "$2" | $MINISHELL > output.txt 2>&1
    cat output.txt
    echo ""
}

### 🔹 Prueba 1: Pipe básico (cat + grep + more)
echo -e "Hola\nbla\nMinishell\nbla bla" > testfile.txt
run_test "Pipe: cat | grep | more" "cat testfile.txt | grep bla | more"

### 🔹 Prueba 2: Pipe con comandos de conteo
run_test "Pipe: ls | wc -l" "ls | wc -l"

### 🔹 Prueba 3: Pipe con comandos de filtrado
echo -e "uno\ndos\ntres\ncuatro" > testfile.txt
run_test "Pipe: cat | grep | sort" "cat testfile.txt | grep tres | sort"

### 🔹 Prueba 4: Pipe con un comando inválido
run_test "Pipe con error: ls archivo_inexistente | grep bla | more" "ls archivo_inexistente | grep bla | more"

### 🔹 Prueba 5: Múltiples pipes en serie
run_test "Pipe largo: cat | grep | sort | wc -l" "cat testfile.txt | grep tres | sort | wc -l"

### 🔹 Prueba 6: Pipes mezclados con redirecciones
echo "Hola mundo" > input.txt
run_test "Mix pipes y redirecciones: cat < input.txt | grep Hola > output.txt" "cat < input.txt | grep Hola > output.txt; cat output.txt"

### 🔹 Prueba 7: Pipe con stdin interactivo
run_test "Pipe con entrada manual: echo | cat | wc -c" "echo 'Hola' | cat | wc -c"

### 🔹 Prueba 8: Pipe con heredoc "<<"
run_test "Pipe con heredoc: heredoc | grep" "cat << EOF | grep bla\nbla bla\nEOF"

echo "===== TEST FINALIZADOS ====="

