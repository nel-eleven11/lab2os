#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    double cpu_time_used;

    // Guardar el tiempo antes de los ciclos
    start = clock();

    // Ejecutar tres ciclos de un millón de iteraciones cada uno, imprimiendo el índice
    for (long i = 0; i < 1000000; i++) {
        printf("Iteración: %ld en ciclo 1\n", i);
    }
    for (long i = 0; i < 1000000; i++) {
        printf("Iteración: %ld en ciclo 2\n", i);
    }
    for (long i = 0; i < 1000000; i++) {
        printf("Iteración: %ld en ciclo 3\n", i);
    }

    // Guardar el tiempo después de los ciclos
    end = clock();

    // Calcular el tiempo transcurrido en segundos
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Imprimir el resultado
    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used);

    return 0;
}
