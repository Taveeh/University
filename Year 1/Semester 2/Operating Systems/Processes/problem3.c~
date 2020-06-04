/*
 * Write a C program that creates two child processes. The two child processes will alternate sending 
 * random integers between 1 and 10(inclusively) to one another until one of them sends the number 10. 
 * Print messages as the numbers are sent.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv) {
	int c1toc2[2], c2toc1[2];
	if (pipe(c1toc2) == -1) {
		perror("Error on pipe 1 -> 2");
		exit(1);
	}
	if (pipe(c2toc1) == -1) {
		perror("Error on pipe 2 -> 1");
		exit(1);
	}
	int pid = fork();
	if (pid == -1) {
		perror("Error on fork");
	}else if (pid == 0) {
		close (c1toc2[0]);
		close (c2toc1[1]);
		int n;
		srand(time(0) ^ getpid());
		if (read(c2toc1[0], &n, sizeof(int)) < 0) {
			perror("Error on read number from child 2");
			close(c1toc2[1]);
			close(c2toc1[0]);
		}
		while (n != 10) {
			n = rand() % 10 + 1;
			if (write(c1toc2[1], &n, sizeof(int)) < 0) {
				perror("Error on write from child1 to child2");
			}	
			if (n == 10) {
				break;
			}
			if (read(c2toc1[0], &n, sizeof(int)) < 0) {
				perror("Error on read number from child 2");
			}
			printf("Child 1 read %d\n", n);
		}
		close(c1toc2[1]);
		close(c2toc1[0]);
		exit(0);
	}else {
		int pid2 = fork();
		if (pid2 == -1) {
			perror("Error on 2nd fork");
		}else if (pid2 == 0) {
			close(c2toc1[0]);
			close(c1toc2[1]);
			int n = 0;
			srand(time(0) ^ getpid());
			while (n != 10) {
				n = random() % 10 + 1;
				if (write(c2toc1[1], &n, sizeof(int)) < 0) {
					perror("Error o write number to child 1");
				}
				if (n == 10) {
					break;
				}
				if (read(c1toc2[0], &n, sizeof(int)) < 0) {
					perror("Error on read number from child 1");
				}
				printf("Child 2 read %d\n", n);
			}
			close(c2toc1[1]);
			close(c1toc2[0]);
			exit(0);
		} else {
			wait(0);
			wait(0);
		}
	}
	return 0;
}
