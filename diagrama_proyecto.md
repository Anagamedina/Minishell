# Diagrama de Flujo para el Proyecto Minishell

```mermaid
flowchart TB
    %% User Input Stage
    subgraph Input
        A([Inicio del Programa]) --> B[Mostrar prompt]
        B --> C[Captura entrada de usuario]
    end

    %% Tokenization and Parsing Stage
    subgraph Tokenization_and_Parsing
        C --> D[Tokenización]
        D --> E[Separar en palabras y operadores]
        E --> F[Respetar reglas de comillas]
        F --> G[Parsear tokens]
    end

    %% Token Processing Stage
    subgraph Token_Processing
        G --> H[Identificar comandos y argumentos]
        H --> I{¿Pipeline?}
        I -->|Sí| J[Pipelines - Redirigir salida de comando previo]
        I -->|No| K{¿Variable?}
        K -->|Sí| L[Expandir variables de entorno]
    end

    %% Expansion and Redirection Stage
    subgraph Expansion_and_Redirection
        L --> M[Expansión de Variables]
        M --> N[Expansión de tilde (~)]
        N --> O[Word Splitting y Quote Removal]
        O --> P{¿Redirección?}
        P -->|<| Q[Redirigir input]
        P -->|>| R[Redirigir output]
        P -->|>>| S[Append output]
        P -->|<<| T[Here Document]
    end

    %% Command Execution Stage
    subgraph Command_Search_and_Execution
        T --> U[Buscar ejecutable en PATH]
        U --> V[Preparar entorno de ejecución]
        V --> W{¿Es un built-in?}
        W -->|Sí| X[Ejecutar built-in]
        W -->|No| Y[Ejecutar comando externo]
    end

    %% Signal Handling Stage
    subgraph Signal_Handling_and_Loop
        Y --> Z{¿Señal de usuario?}
        Z -->|Ctrl-C| AA[Nueva línea en prompt]
        Z -->|Ctrl-D| AB[Terminar shell]
        Z -->|Ctrl-\| AC[Ignorar]
        AA --> B
        AB --> END([Fin del Programa])
    end
