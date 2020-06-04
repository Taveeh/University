#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/*
 *  Create a C program that runs a bash command received as a command line argument - popen.
 */
int main(int argc, char** argv) {
	if (argc < 2) {
		printf("Invalid command\n");
		exit(1);
	}
	char* buf = (char*)malloc(100* sizeof(char));
	memset(buf, 0, 100 * sizeof(char));
	char* cmd = (char*)malloc(100* sizeof(char));
	memset(cmd, 0, 100 * sizeof(char));
	int i = 0;
	for (i = 0; i < argc - 1; ++i) {
		strcat(cmd, argv[i + 1]);
		strcat(cmd, " ");
	}
	FILE* file = popen(cmd, "r");
	if (file == NULL) {
		perror("Error on popen");
	}else {
		int k;
		while ((k = fread(buf, 1, 100, file)) > 0 ) {
			printf("%s", buf);
			memset(buf, 0, 100 * sizeof(char));
		}
		printf("\n");
	}
	pclose(file);
	free(buf);
	free(cmd);
	return 0;
}
