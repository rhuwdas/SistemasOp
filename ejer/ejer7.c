#include <stdio.h>

#include <unistd.h>

#include <string.h>

#include <stdlib.h>


int main (int argc, char *argv[]) {
        /* ./ejer7 EPEP AJSD*/
        int i;

        printf("Ejecutando el programa invocador (Ejercicio 7). Sus argumentos son:\n");

        for (i = 0; i < argc; i++)

                printf("argv[%d]: %s\n", i, argv[i]);

        sleep(2);

        strcpy(argv[0], "PEPE PICA PAPAS CON UN PICO");

        if (execv ("./ejer8", argv) < 0) {

                printf("Error en la invocacion del Ejercicio-8\n");

                exit(1);

        };

        exit(0);

}
