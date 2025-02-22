#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_hijo, pid_nieto, pid_bisnieto;
    clock_t start, end;
    double elapsed_time;

    // Guardar el tiempo antes del primer fork()
    start = clock();

    pid_hijo = fork();

    if (pid_hijo == 0) {  // Proceso hijo
        pid_nieto = fork();

        if (pid_nieto == 0) {  // Proceso nieto
            pid_bisnieto = fork();

            if (pid_bisnieto == 0) {  // Proceso bisnieto
                // Bisnieto: ejecutar un ciclo for de 1 millón de iteraciones imprimiendo el índice
                for (long i = 0; i < 1000000; i++) {
                    printf("Iteración: %ld en bisnieto (PID: %d)\n", i, getpid());
                }
            } else {  // Proceso nieto espera al bisnieto
                wait(NULL);
                // Nieto: ejecutar un ciclo for de 1 millón de iteraciones
                for (long i = 0; i < 1000000; i++) {
                    printf("Iteración: %ld en nieto (PID: %d)\n", i, getpid());
                }
            }
        } else {  // Proceso hijo espera al nieto
            wait(NULL);
            // Hijo: ejecutar un ciclo for de 1 millón de iteraciones
            for (long i = 0; i < 1000000; i++) {
                printf("Iteración: %ld en hijo (PID: %d)\n", i, getpid());
            }
        }
    } else {  // Proceso padre espera al hijo
        wait(NULL);
        // Guardar el tiempo después de la ejecución del hijo
        end = clock();

        // Calcular el tiempo transcurrido en segundos
        elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Imprimir el resultado
        printf("Tiempo de ejecución: %f segundos\n", elapsed_time);
    }

    return 0;
}
