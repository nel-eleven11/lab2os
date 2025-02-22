#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

#define SHM_NAME "/mi_memoria_compartida"
#define SHM_SIZE 64

int main() {
    printf("Soy el proceso principal\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al hacer fork()");
        return 1;
    }

    if (pid == 0) {
        // Proceso hijo
        printf("Soy el proceso b\n");

        int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1) {
            perror("Error al abrir memoria compartida");
            return 1;
        }
        printf("b: Memoria compartida creada con descriptor %d\n", shm_fd);

        ftruncate(shm_fd, SHM_SIZE);
        void *shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (shm_ptr == MAP_FAILED) {
            perror("Error al mapear memoria compartida");
            return 1;
        }
        printf("b: Puntero a memoria compartida: %p\n", shm_ptr);

        memset(shm_ptr, 'b', SHM_SIZE / 2);  // Llenar la mitad con 'b'
        printf("b: Memoria compartida tiene: %s\n", (char *)shm_ptr);

        munmap(shm_ptr, SHM_SIZE);
        close(shm_fd);
    } else {
        // Proceso padre
        sleep(1);  // Esperar a que el hijo inicie primero
        printf("Soy el proceso a\n");

        int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
        if (shm_fd == -1) {
            perror("Error al abrir memoria compartida existente");
            return 1;
        }
        printf("a: Memoria compartida ya existe con descriptor %d\n", shm_fd);

        void *shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        if (shm_ptr == MAP_FAILED) {
            perror("Error al mapear memoria compartida");
            return 1;
        }
        printf("a: Puntero a memoria compartida: %p\n", shm_ptr);

        memset(shm_ptr + (SHM_SIZE / 2), 'a', SHM_SIZE / 2);  // Llenar la otra mitad con 'a'
        printf("a: Memoria compartida tiene: %s\n", (char *)shm_ptr);

        munmap(shm_ptr, SHM_SIZE);
        close(shm_fd);
        shm_unlink(SHM_NAME);
    }

    return 0;
}
