#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define SHM_NAME "/mi_memoria_compartida"  // Nombre de la memoria compartida
#define SHM_SIZE 1024  // Tamaño de la memoria compartida

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <número> <letra>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);  // Convertir argumento a entero
    char x = argv[2][0];    // Obtener la letra

    int shm_fd;
    void *shm_ptr;
    
    // Intentar abrir la memoria compartida
    shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        // Si no existe, crearla
        shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1) {
            perror("Error al abrir la memoria compartida");
            return 1;
        }
        // Configurar el tamaño de la memoria compartida
        if (ftruncate(shm_fd, SHM_SIZE) == -1) {
            perror("Error al ajustar tamaño de memoria compartida");
            return 1;
        }
        printf("Memoria compartida creada con descriptor %d\n", shm_fd);
    } else {
        printf("Memoria compartida existente encontrada con descriptor %d\n", shm_fd);
    }

    // Mapear la memoria compartida
    shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("Error al mapear la memoria compartida");
        return 1;
    }

    // Crear pipe para comunicación entre padre e hijo
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Error al crear el pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Error al crear proceso hijo");
        return 1;
    }

    if (pid == 0) {  
        // Proceso hijo: Lee del pipe y escribe en memoria compartida
        close(pipe_fd[1]);  // Cerrar escritura en el pipe

        char buffer[SHM_SIZE] = {0};
        int index = 0;
        while (read(pipe_fd[0], &buffer[index], 1) > 0) {
            index++;
        }

        strncpy((char*)shm_ptr, buffer, SHM_SIZE);
        close(pipe_fd[0]);  // Cerrar lectura del pipe

    } else {  
        // Proceso padre: Recorre el ciclo y envía datos al hijo
        close(pipe_fd[0]);  // Cerrar lectura en el pipe

        for (int i = 1; i < SHM_SIZE; i++) {
            if (i % n == 0) {
                write(pipe_fd[1], &x, 1);
            }
        }

        close(pipe_fd[1]);  // Cerrar escritura del pipe
        wait(NULL);  // Esperar al proceso hijo

        // Desplegar el contenido de la memoria compartida
        printf("Contenido en memoria compartida:\n%s\n", (char*)shm_ptr);

        // Liberar recursos
        munmap(shm_ptr, SHM_SIZE);
        shm_unlink(SHM_NAME);
    }

    return 0;
}
