#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Crear un nuevo proceso

    if (pid == 0) {  
        // Proceso hijo: Cuenta del 1 al 4,000,000
        for (long i = 1; i <= 4000000; i++) {
            if (i % 1000000 == 0) {
                printf("Contando: %ld\n", i);
                fflush(stdout);
            }
        }
    } else if (pid > 0) {  
        // Proceso padre: Espera al hijo y luego entra en un bucle infinito
        wait(NULL);
        while (1) { }
    } else {
        // Error al hacer fork()
        perror("Error al crear el proceso hijo");
        return 1;
    }

    return 0;
}
