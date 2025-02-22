#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    // Verificar si se pasaron los argumentos correctos
    if (argc != 3) {
        printf("Uso: %s <número> <letra>\n", argv[0]);
        return 1;
    }

    // Convertir el primer argumento a entero
    int n = atoi(argv[1]);

    // Obtener la letra del segundo argumento
    char x = argv[2][0];

    // Mostrar los valores ingresados
    printf("Número recibido: %d\n", n);
    printf("Letra recibida: %c\n", x);

    return 0;
}
