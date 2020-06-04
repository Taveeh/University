/*
 * Write a C program that implements the boltz game. N processes (numbered 1 to N, where N is given) take turns incrementing a number and sending it to the next process. Process 1 starts the game by incrementing the number and sends it to process 2, which increments and sends it to process 3 and so on. Process N will send the number back to process 1. Each process must print the number it sends, unless the number contains the digit 7 or is divisible by 7, in which case it must print "boltz". Implement so that each process has a 1 in 10 chance to fail printing "boltz" when it should, in which case the game stops.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
int containsSeven(int n);
int divisibleBySeven(int n);
int shouldSayBoltz(int n) {
	return containsSeven(n) || divisibleBySeven(n);
}
void play(int id, int read_from, int write_to) {
	int number = 1;
	srand(getpid() ^ time(0));
	while (number >= 0) {
		if (read(read_from, &number, sizeof(int)) < 0) {
			perror("Error on read number from pipe");
			number = -1;
		}
		if (id != 0) {
			if (number >= 0) {
				int chance = rand() % 10;
				number++;
				if (shouldSayBoltz(number)) {
					if (chance == 0) {
						printf("Player %d -> %d -> Failed\n", id, number);
						number = -1;
					}else {
						printf("Player %d -> BOLTZ\n", id);
						number++;
					}
				}else {
					printf("Player %d -> %d\n", id, number);
				}
			}else {
				printf("Player %d received %d -> Exiting...\n", id, number);
			}
			if (write(write_to, &number, sizeof(int)) < 0) {
				perror("Error on write to pipe");
			}
		}else {
			if (number <= 0) {
				printf("You cannot beat me, I created you");
			}else {
				number++;
				char nr[6] = "BOLTZ";
				scanf("%s", nr);
				if (shouldSayBoltz(number)) {
					printf("%s", nr);
					if (strcmp(nr, "BOLTZ") == 0) {
						strcpy(nr, "BOLTZ");
					}else {
						number = -1;
					}
					//printf("Player %d -> BOLTZ\n", id);
					//number++;
				}else {
					int num = atoi(nr);
					if (num == number) {
						num = number;
					}else {
						number = -1;
					}
					//printf("Player %d -> %d\n", id, number);
					//number++;
				}
				if (write(write_to, &number, sizeof(int)) < 0) {
					perror("Error on write to pipe");
				}
			}
		}
	}
}
int main(int argc, char** argv) {
	if (argc != 2) {
		perror("Please enter exactly one argument");
		exit(1);
	}
	int i, n = atoi(argv[1]);
	int children[n - 1], p[n][2];
	for (i = 0; i < n; ++i) {
		pipe(p[i]);
	}
	if (n <= 1) {
		perror("Please enter a number >=2");
		exit(1);
	}
	for (int i = 0; i < n - 1; ++i) {
		children[i] = fork();
		if (children[i] == -1) {
			perror("Error on fork");
			exit(1);
		}else if (children[i] == 0) {
			int id = i + 1;
			int read_from = id;
			int write_to = (id + 1) % n;
			play(id, p[read_from][0], p[write_to][1]);
			exit(0);
		}
	}

	int number;
	printf("Please start the game: ");
	scanf("%d", &number);
	int id = 0;
	int read_from = id;
	int write_to = id + 1;
	srand(getpid() ^ time(0));
	printf("Player %d -> %d\n", id, number);
	if (number != 1) {
		printf("That's why we don't like humans");
		number = -1;
	}
	if (write(p[write_to][1], &number, sizeof(int)) < 0) {
		perror("Error on write to pipe");
	}
	play(id, p[read_from][0], p[write_to][1]);
	for (i = 0; i < n; ++i) {
		wait(0);
	}
	for (i = 0; i < n; ++i) {
		close(p[i][0]);
		close(p[i][1]);
	}
	return 0;
}

int containsSeven(int n) {
	while (n != 0) {
		if (n % 10 == 7) {
			return 1;
		}
		n /= 10;
	}
	return 0;
}
int divisibleBySeven(int n) {
	return (n % 7 == 0);
}

