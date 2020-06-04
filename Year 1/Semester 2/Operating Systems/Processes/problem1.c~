#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 
 * Create a C program that runs a bash command received as a command line argument - exec.
 */
int main(int argc, char** argv) {
	printf("%d\n", argc);
	if (argc < 2) {
		printf("Invalid command\n");
		exit(1);
	}
	int pid = fork();
	if (pid == -1) {
		perror("Error on fork\n");
		exit(1);
	}
	if (pid == 0) {
		execvp(argv[1], argv + 1);
		perror("Error on exec\n");
		exit(1);
	}
	wait(0);
	return 0;
}
