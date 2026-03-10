#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/types.h>

int main()

{

system("clear");

printf ("Creación de un proceso...\n\n\n");

pid_t pid;

pid = fork();

if (pid < 0) {    // Error

printf("Error al crear el proceso\n");

  } else if (pid == 0) { //Código del proceso hijo

printf ("Proceso Hijo. PID: %d\n", getpid());

} else {            // Código del proceso

printf("Proceso Padre, PID: %d\n", getpid());

printf("Proceso Hijo, PID: %d\n", pid);


}

return 0;
}
