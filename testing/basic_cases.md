Aquí tienes ejemplos básicos para probar los **built-ins** en tu programa **minishell**. Estos casos son comunes y cubren escenarios básicos de cada comando:

---

### **1. `echo`**
```bash
echo Hello World       # Imprime "Hello World" seguido de un salto de línea
echo -n Hello World    # Imprime "Hello World" sin salto de línea final
echo "Hello $USER"     # Expande variables (debe mostrar "Hello <valor de USER>")
echo                   # Imprime una línea en blanco
```

---

### **2. `cd`**
```bash
cd /                  # Cambia al directorio raíz
cd ..                 # Cambia al directorio padre
cd                    # Cambia al directorio $HOME
cd nonexistent_dir    # Error: directorio no existe
cd /usr/bin && pwd    # Cambia a /usr/bin y muestra el directorio actual
```

---

### **3. `pwd`**
```bash
pwd                   # Muestra el directorio actual
cd / && pwd           # Debe mostrar "/"
cd .. && pwd          # Muestra el directorio padre del actual
```

---

### **4. `export`**
```bash
export VAR=value      # Define una nueva variable de entorno
export VAR2="Hello"   # Define una variable con espacios
export VAR=value VAR2=value2  # Define múltiples variables
env | grep VAR        # Verifica si las variables se añadieron al entorno
export VAR=           # Define la variable con un valor vacío
```

---

### **5. `unset`**
```bash
export TEMP_VAR=123   # Define una variable temporal
unset TEMP_VAR        # Elimina la variable
echo $TEMP_VAR        # Debe estar vacío (no mostrar nada)
unset PATH            # Cuidado: Elimina PATH (no funcionarán comandos externos)
```

---

### **6. `env`**
```bash
env                   # Muestra todas las variables de entorno
env | grep PATH       # Busca y muestra solo la variable PATH
export TEST_VAR=42    # Agrega una variable
env | grep TEST_VAR   # Verifica si TEST_VAR está en el entorno
```

---

### **Cómo Probar**
1. Ejecuta cada comando en tu programa y compara los resultados con el comportamiento de **Bash**.
2. Usa casos como redirecciones y pipes para validar la integración con otras partes de tu shell:
   ```bash
   echo Hello | grep H
   cd /usr && pwd > output.txt
   ```

Estos casos te ayudarán a validar las funcionalidades básicas de los built-ins.

ls -l | grep text > output.txt
