#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/types.h>

int main()

{

system("clear");

printf ("Proceso para ejecutar Comando de Sistema...\n\n\n");

pid_t pid;

pid = fork(); //Proceso Hijo

if (pid < 0) {    // Error

printf("Error al crear el proceso\n");

  } else if (pid == 0) { //Código del proceso hijo

printf ("Proceso Hijo. PID: %d\n", getpid());

} else {            // Código del proceso

printf("Proceso Padre, PID: %d\n", getpid());

printf("Proceso Hijo, PID: %d . . .   Completado . . .\n", pid);

//execlp("/bin/ls", "ls", "-la",  NULL);

execlp("top", NULL, NULL,  NULL);

exit(0);

}

return 0;

}
