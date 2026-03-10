
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


pid_t pid_hijo;


/* Función que ejecuta el hijo cuando recibe SIGUSR1 */

void hijo(int sig) {

    printf("\t\t[HIJO] ¡Padre! ¿Qué haces?\n");

    printf("\t\t[HIJO] Muere el Hijo, PID: %d\n", getpid());


    /* enviar señal al padre */

    kill(getppid(), SIGUSR1);


    exit(0);

}


/* Función que ejecuta el padre cuando recibe SIGUSR1 */

void padre(int sig) {

    printf("\t[PADRE] ¡Hijo! ¿Qué he hecho?\n");

    printf("\t[PADRE] Final del Padre, PID: %d\n", getpid());


    /* esperar al hijo para evitar zombie */

    wait(NULL);


    exit(0);

}


int main() {


    pid_t rf;


    rf = fork();


    if (rf < 0) {

        perror("Error al crear el proceso hijo");

        exit(1);

    }


    if (rf == 0) {

        /* PROCESO HIJO */


        printf("\t\tSoy el HIJO\n");

        printf("\t\tPID: %d\n", getpid());

        printf("\t\tMi padre es PPID: %d\n", getppid());


        /* registrar señal */

        signal(SIGUSR1, hijo);


        /* esperar señal */

        while(1) pause();

    }

    else {

        /* PROCESO PADRE */


        pid_hijo = rf;


        printf("Soy el PADRE\n");

        printf("PID: %d\n", getpid());

        printf("PID de mi Hijo: %d\n", pid_hijo);


        /* registrar señal */

        signal(SIGUSR1, padre);


        sleep(3);


        printf("[PADRE] Voy a matar a mi hijo...\n");


        /* enviar señal al hijo */

        kill(pid_hijo, SIGUSR1);


        /* esperar señal del hijo */

        while(1) pause();

    }


    return 0;

}
