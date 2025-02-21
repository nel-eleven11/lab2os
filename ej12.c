#include <stdio.h>
#include <unistd.h>

int main() {
	for (int i = 0; i < 4; i++) {
		fork();
	}
	printf("Proceso: PID = %d, PPID = %d\n", getpid(), getppid());
	return 0;
}
