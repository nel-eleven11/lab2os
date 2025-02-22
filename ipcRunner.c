#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al hacer fork()");
        return 1;
    }

    if (pid == 0) {
        // Proceso hijo: Ejecuta ipc con x = '#'
        execl("./ipc", "./ipc", "5", "#", NULL);
        perror("Error en execl (hijo)");
        return 1;
    } else {
        // Proceso padre: Ejecuta ipc con x = '@'
        execl("./ipc", "./ipc", "3", "@", NULL);
        perror("Error en execl (padre)");
        return 1;
    }

    return 0;
}
