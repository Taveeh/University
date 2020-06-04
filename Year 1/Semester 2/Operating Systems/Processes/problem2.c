#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*
 * Create a C program that generates N random integers (N given at the command line). It then creates a child, sends the numbers via pipe. The child calculates the average and sends the result back.*/

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Please provide exactly one argument.\n");
		exit(1);
	}
	int parent_to_child[2], child_to_parent[2];
	pipe(parent_to_child);
	pipe(child_to_parent);
	pid_t pid = fork();
	if (pid == -1) {
		perror("Error on fork.\n");
		exit(1);
	}else if (pid == 0) {
		close(parent_to_child[1]);
		close(child_to_parent[0]);
		int n, nr, i;
		float rez = 0;
		if (read(parent_to_child[0], &n, sizeof(int)) < 0) {
			perror("Error on read N from parent\n");
			close(parent_to_child[0]);
			close(child_to_parent[1]);
			exit(1);
		}
		for (i = 0; i < n; ++i) {
			if (read(parent_to_child[0], &nr, sizeof(int)) < 0) {
				perror("Error on read number from parent");
				close(parent_to_child[0]);
				close(child_to_parent[1]);
			}
			rez += nr;
		rez /= n;
		}
	if (write(child_to_parent[1], &rez, sizeof(float)) < 0) {
		perror("Error on write result to parent. \n");
		close(parent_to_child[0]);
		close(child_to_parent[1]);
		exit(1);
	}
	close(parent_to_child[0]);
	close(child_to_parent[1]);
	exit(0);
	} else {
		close(parent_to_child[0]);
		close(child_to_parent[1]);
		int nr = atoi(argv[1]);
		int i = 0;
		float rez;
		int n;
		srandom(time(0));
		if (write(parent_to_child[1], &nr, sizeof(int)) < 0) {
			perror("Error on write n to child\n");
		}
		for (i = 0; i < nr; ++i) {
			n  = rand() % 100;
			printf("Parent generated %d\n", n);
			if (write(parent_to_child[1], &n, sizeof(int)) < 0) {
				perror("Error on write parent to child");
				close(parent_to_child[1]);
				close(child_to_parent[0]);
			}
		}
		int status;
		wait(&status);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
			if (read(child_to_parent[0], &rez, sizeof(float)) < 0) {
				perror("Error on read result from file");
			}
			printf("Average is %f\n", rez);
		}
		close(parent_to_child[1]);
		close(child_to_parent[0]);
	}
	return 0;
}
