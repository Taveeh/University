#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
	int ptc[2], ctp[2];
	if (pipe(ptc) < 0) {
		perror("Error on create pipe");
		exit(1);
	}
	if (pipe(ctp) < 0) {
		perror("Error on create pipe");
		exit(1);
	}
	int pid = fork();
	if (pid == -1) {
		perror("Error on fork");
	}else if (pid == 0) {
		close(ptc[1]);
		close(ctp[0]);
		int n;
		while (n >= 5) {
			if (read(ptc[0], &n, sizeof(int)) < 0) {
				perror("Error on read to pipe");
			}else {
				n /= 2;
				printf("B -> %d\n", n);

				if (write(ctp[1], &n, sizeof(int)) < 0) {
					perror("Error on write to pipe");
				}
			}
		}
	return 0;
}
