/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasalaza <dasalaza@student.42barcelona.c>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:23:28 by dasalaza          #+#    #+#             */
/*   Updated: 2025/02/17 11:23:28 by dasalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Función manejadora que se ejecuta al recibir SIGINT
void manejar_SIGINT(int signum) {
    printf("Señal SIGINT recibida (Ctrl+C). Ignorando la interrupción.\n");
}

int main() {
    // Configura signal para capturar SIGINT y llamar a manejar_SIGINT
    signal(SIGINT, manejar_SIGINT);

    printf("Presiona Ctrl+C para enviar SIGINT.\n");

    // Bucle infinito para mantener el programa activo
    while (1) {
        printf("Esperando señal...\n");
        sleep(2);
    }

    return 0;
}

