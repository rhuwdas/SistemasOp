#include <stdio.h>

#include <unistd.h>

#include <string.h>

#include <stdlib.h>


int main (int argc, char *argv[]) {

        system("clear");

        int i;

        printf("Ejecutando el programa invocador (Ejercicio 7). Sus argumentos son:\n");

        for (i = 0; i < argc; i++)

                printf("argv[%d]: %s\n", i, argv[i]);

        sleep(5);

        char *argv2[6];

        char arg[5][20];

        for (i = 0; i < 5; i++){

                printf ("Argumento [%d]: ",i);

                scanf ("%s",arg[i]);

        }

        strcpy(argv2[0], "./ejemplo8");

        for (i=0; i<5; i++)

                argv2[i+1]=arg[i];

        if (execv ("./ejemplo8", argv2) < 0) {

                printf("Error en la invocacion del Ejercicio-8\n");

                exit(1);

        };

        exit(0);

}
