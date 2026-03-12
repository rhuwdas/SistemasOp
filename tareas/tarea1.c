#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

volatile sig_atomic_t crear_hijo = 0;  // Bandera para lanzar un hijo
pid_t hijo_pid = 0;                    // PID del hijo activo (0 si ninguno)

// Manejador de SIGINT (Ctrl+C)
void manejador_sigint(int sig) {
    if (hijo_pid == 0) {               // Solo si no hay hijo en ejecución
        crear_hijo = 1;
    }
}

// Función que muestra una barra de progreso animada
void barra_progreso(const char *nombre, int pid) {
    for (int i = 0; i <= 100; i += 10) {
        int num_hashes = i / 5;         // 20 caracteres máximos (cada 5% un #)
        printf("\r%s [PID %d] %3d%% ", nombre, pid, i);
        for (int j = 0; j < num_hashes; j++) {
            printf("#");
        }
        for (int j = num_hashes; j < 20; j++) {
            printf(" ");
        }
        fflush(stdout);
        sleep(1);                  // 0.2 segundos por paso
    }
    printf("\n");                        // Línea nueva al terminar
}

int main() {
    // Configurar el manejador para SIGINT
    struct sigaction sa;
    sa.sa_handler = manejador_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    int pid_padre = getpid();
    printf("Mostrando progreso principal. Presiona Ctrl+C para lanzar un hijo.\n");

    for (int i = 0; i <= 100; i += 10) {
        // Si no hay hijo activo, mostramos la barra del padre
        if (hijo_pid == 0) {
            int num_hashes = i / 5;
            printf("\rPadre [PID %d] %3d%% ", pid_padre, i);
            for (int j = 0; j < num_hashes; j++) printf("#");
            for (int j = num_hashes; j < 20; j++) printf(" ");
            fflush(stdout);
        }

        // Comprobar si debemos crear un hijo (por Ctrl+C)
        if (crear_hijo) {
            crear_hijo = 0;
            hijo_pid = fork();
            if (hijo_pid == 0) {
                // Proceso hijo: restaura el manejador por defecto y muestra su barra
                signal(SIGINT, SIG_DFL);
                printf("\nInterrupción recibida. Creando proceso hijo...\n");
                barra_progreso("Hijo", getpid());
                printf("Hijo: Completado\n");
                exit(0);
            } else if (hijo_pid < 0) {
                perror("fork");
                hijo_pid = 0;
            } else {
                // Padre: anuncia la creación y continúa sin imprimir su barra
                printf("\nHijo creado con PID %d. El padre continúa en segundo plano.\n", hijo_pid);
                fflush(stdout);
            }
        }

        // Simula trabajo del padre
        sleep(3);  // 0.5 segundos

        // Verificar si el hijo ya terminó (sin bloquear)
        if (hijo_pid > 0) {
            int status;
            pid_t result = waitpid(hijo_pid, &status, WNOHANG);
            if (result == hijo_pid) {
                printf("\nHijo terminado. Continuando padre...\n");
                hijo_pid = 0;  // Ya no hay hijo activo
                // En la siguiente iteración se volverá a mostrar la barra del padre
            } else if (result == -1) {
                perror("waitpid");
                hijo_pid = 0;
            }
        }
    }

    // Si al finalizar el padre aún hay un hijo, esperamos a que termine
    if (hijo_pid > 0) {
        waitpid(hijo_pid, NULL, 0);
        printf("\nHijo terminado. Progreso del padre completado.\n");
    }
    printf("\nProgreso del padre completado.\n");
    return 0;
}
