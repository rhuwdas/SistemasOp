#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <signal.h>

#include <sys/types.h>


#define VUELTAS 900000000LL


void confirmar(int sig){

char resp[100];

write (1,"¿Quieres terminar (s/n) ?",24);

read (0, resp, 100);

if (resp[0]=='s')

    exit(0);

}


int main(void){

system("clear");

printf ("Interrupciones de un proceso...\n\n\n");

long long int i;

write (1, "No hago caso a Control-C \n\n",28);

signal(SIGINT, SIG_IGN);


for (i=0; i<VUELTAS; i++){}

write (1, "\nYa hago caso a Control-C \n",28);
i=0;
signal(SIGINT, SIG_DFL);

for (i=0; i<VUELTAS; i++){}



write (1, "Ahora eres libre de elegir . . .",32);

signal(SIGINT, *confirmar);

for (i=0; i<VUELTAS; i++){}


exit (0);

}

