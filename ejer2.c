#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/types.h>

int main()

{

system("clear");

printf ("Creación de un proceso...\n\n\n");

pid_t pid  = fork();

if (pid < 0) {    // Error

printf("Error al crear el proceso\n");

return 1;

} else if (pid == 0) { //Código del proceso hijo

printf ("Proceso Hijo en ejecución. PID: %d\n", getpid());

sleep (15); //Estado en Espera...

printf ("Hijo Terminado...\n\n");

} else {            // Código del proceso

printf("Proceso Padre, PID: %d\n", getpid());

printf("Proceso Hijo, PID: %d\n", pid);

printf ("Estado del Proceso Hijo:\n");

sleep(15);

char comando[100];

sprintf(comando, "ps -o pid,ppid,state,cmd -p %d", pid);

system(comando);

sleep(15); //Esperar que el roceso hijo termine

printf("\nEstado después de que el hijo termine:\n");

system(comando);

}

return 0;

}
