#include <stdio.h>
#include <time.h>

int main() {
    clock_t start, end;
    double cpu_time_used;
    double cpu_time_used_sec;

    // Guardar el tiempo antes de los ciclos
    start = clock();

    // Ejecutar tres ciclos de un millón de iteraciones cada uno
    for (long i = 0; i < 1000000; i++);
    for (long i = 0; i < 1000000; i++);
    for (long i = 0; i < 1000000; i++);

    // Guardar el tiempo después de los ciclos
    end = clock();

    // Calcular el tiempo transcurrido en segundos
    cpu_time_used = ((double)(end - start));
    cpu_time_used_sec = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Imprimir el resultado
    printf("Tiempo de ejecución: %f \n", cpu_time_used);
    printf("Tiempo de ejecución: %f segundos\n", cpu_time_used_sec);

    return 0;
}
