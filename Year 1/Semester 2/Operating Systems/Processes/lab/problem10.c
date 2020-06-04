#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

/*
 * 10. Write a program that receives strings of alphanumeric characters as command line arguments (validation is not required). For each string the program creates a thread which calculates the number of digits, the number of consonants and the number of vowels. The thread adds the results to three global variables, one for digits, one for vowels and one for consonants. The main program prints the end results (total number of digits, vowels and consonants across all the received command line arguments) and terminates. Use efficient synchronization.
 */
int nrVoc = 0, nrCon = 0, nrDig = 0;
pthread_mutex_t mutexVoc;
pthread_mutex_t mutexCon;
pthread_mutex_t mutexDig;
void *th_function(void* a) {
	char* sir = (char*)a;

	int i = 0;
	for (i = 0; i < strlen(sir); ++i) {
		if (sir[i] >= '0' && sir[i] <= '9') {
			pthread_mutex_lock(&mutexDig);
			nrDig++;
			pthread_mutex_unlock(&mutexDig);
		}else if (strchr("aeiou", sir[i]) != NULL) {
			pthread_mutex_lock(&mutexVoc);
			nrVoc++;
			pthread_mutex_unlock(&mutexVoc);
		}else if (sir[i] >= 'a' && sir[i] <= 'z') {
			pthread_mutex_lock(&mutexCon);
			nrCon++;
			pthread_mutex_unlock(&mutexCon);
		}
	}
	return NULL;
}
int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Please provide at least one string");
		exit(1);
	}
	if (0 != pthread_mutex_init(&mutexVoc, NULL)) {
		perror("Error creating mutex");
		exit(1);
	}
	if (0 != pthread_mutex_init(&mutexCon, NULL)) {
		perror("Error creating mutex");
		exit(1);
	}
	if (0 != pthread_mutex_init(&mutexDig, NULL)) {
		perror("Error creating mutex");
		exit(1);
	}
	int i;
	pthread_t threads[argc - 1];
	for (i = 0; i < argc - 1; ++i) {
		if (0 != pthread_create(&threads[i], NULL, &th_function, argv[i + 1])) {
			perror("Error on create	thread");
		}
	}
	
	for (i = 0; i < argc - 1; ++i) {
		if (0 != pthread_join(threads[i], NULL)) {
			perror("Error waiting for thread");
		}
	}

	pthread_mutex_destroy(&mutexVoc);
	pthread_mutex_destroy(&mutexCon);
	pthread_mutex_destroy(&mutexDig);

	printf("Vowels: %d, Consonants: %d, Digits: %d\n", nrVoc, nrCon, nrDig);
	return 0;
}
