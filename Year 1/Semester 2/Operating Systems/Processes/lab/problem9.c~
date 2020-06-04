#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Please provide at least 1 parameter");
		exit(1);
	}
	int atob[2], btoc[2], ctoa[2];
	pipe(atob);
	pipe(btoc);
	pipe(ctoa);
	int pid1 = fork();
	if (pid1 == -1) {
		perror("Error on 1st fork");
	}else if (pid1 == 0) {
		close(atob[1]);
		close(ctoa[0]);
		close(ctoa[1]);
		close(btoc[0]);
		int nr, number, i;
		srand(time(0));
		if (read(atob[0], &number, sizeof(int)) < 0) {
			perror("Error on read");
		}else {
			if (write(btoc[1], &number, sizeof(int)) < 0) {
				perror("Error on write to pipe");
			}else {
				for (i = 0; i < number; ++i) {
					if (read(atob[0], &nr, sizeof(int)) < 0) {
						perror("Error on read");
					}else {
						int ran = rand() % 4 + 2;
						nr += ran;
						if (write(btoc[1], &nr, sizeof(int)) < 0) {
							perror("Error on write to pipe");
						}
					}
				}
			}
		}
		close(atob[0]);
		close(btoc[1]);
		exit(0);
	}else {
		int pid2 = fork();
		if (pid2 == -1) {
			perror("Error on fork 2");
		}else if (pid2 == 0) {
			close(atob[0]);
			close(atob[1]);
			close(btoc[1]);
			close(ctoa[0]);
			int number, sum = 0, nr, i;
			if (read(btoc[0], &number, sizeof(int)) < 0) {
				perror("Error on read from pipe");
			}else {
				for (i = 0; i < number; ++i) {
					if (read(btoc[0], &nr, sizeof(int)) < 0) {
						perror("Error on read");
					}else {
						sum += nr;
					}
				}
			}
			if (write(ctoa[1], &sum, sizeof(int)) < 0) {
				perror("Error on write sum to A");
			}
		}else {
			close(atob[0]);
			close(btoc[0]);
			close(btoc[1]);
			close(ctoa[1]);
			int n = atoi(argv[1]), i, total;
			if (write(atob[1], &n, sizeof(int)) < 0) {
				perror("Error on write number to pipe");
			}else {
				for (i = 0; i < n; ++i) {
					int nr;
					scanf("%d", &nr);
					printf("Writing %d to B\n", nr);
					if (write(atob[1], &n, sizeof(int)) < 0) {
						perror("Error on write to pipe");
					}
					printf("Wrote %d to B\n", nr);
				}
			}
			if (read(ctoa[0], &total, sizeof(int)) < 0) {
				perror("Error on read total from pipe");
			}else {
				printf("Total sum: %d\n", total);
			}
			wait(0);
			wait(0);
		}
	}
	return 0;
}
