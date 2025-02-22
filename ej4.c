#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // Crear un nuevo proceso

    if (pid == 0) {  
        // Este es el proceso hijo
        printf("Soy el proceso hijo (PID: %d)\n", getpid());
    } else if (pid > 0) {  
        // Este es el proceso padre
        while (1) {
            // Ciclo infinito en el proceso padre
        }
    } else {
        // Error al hacer fork()
        perror("Error al crear el proceso hijo");
        return 1;
    }

    return 0;
}

