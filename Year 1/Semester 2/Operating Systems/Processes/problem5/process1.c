#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "common.h"
#include <errno.h>
#include <string.h>
#include <fcntl.h>
void makeFifoIfNotExist(char* fifoName);
void handler(int sig);
void writeToFifo(int fd, char* buf);
int main(int argc, char** argv) {
	int fd, k;
	char *cmd;
	FILE* f;
	cmd = (char*)malloc(SIZE * sizeof(char));
	memset(cmd, 0, SIZE * sizeof(char));
	char *buf;
	buf = (char*)malloc(SIZE * sizeof(char));
	memset(buf, 0, SIZE * sizeof(char));

	signal(SIGINT, handler);
	
	makeFifoIfNotExist(myfifo);
	if ((fd = open(myfifo, O_WRONLY)) < 0) {
		perror("Error on open file");
		exit(1);
	}

	while (1) {
		if ((k = read(0, cmd, SIZE * sizeof(char))) < 0) {
				perror("Error on read from console");
		}
		cmd[k - 1] = 0;
		if (strcmp(cmd, "stop") == 0) {
			printf("Exiting...");
			break;
		}
		if ((f = popen(cmd, "r")) == NULL) {
			perror("Error on popen");
		}else {
			while(fread(buf, 1, SIZE - 1, f) > 0) {
				writeToFifo(fd, buf);
				memset(buf, 0, SIZE * sizeof(char));
			}
		}
		pclose(f);
		memset(cmd, 0, SIZE * sizeof(char));
	}
	int stop = -1;
	if (write(fd, &stop, sizeof(int)) > 0) {
		perror("Error on write stop to fifo");
	}
	close(fd);
	free(cmd);
	free(buf);
	if (unlink(myfifo) < 0) {
		perror("Unlink failed");
		exit(1);
	}
	return 0;
}

void writeToFifo(int fd, char* buf) {
	int nr = strlen(buf);
	if (write(fd, &nr, sizeof(int)) < 0) {
		perror("Error on write size to fifo");
	}
	if (write(fd, buf, SIZE * sizeof(char)) < 0) {
		perror("Error on wirte message to fifo");
	}
}
void handler(int sig) {
	printf("\nSIGINT received; removing fifo.\n");
	if (unlink(myfifo) < 0) {
		perror("Unlink failed");
		exit(1);
	}
	exit(0);
}
void makeFifoIfNotExist(char* fifoName) {
	struct stat stats;
	if (stat(fifoName, &stats) < 0) {
		if (errno != ENOENT) {
			perror("Error on stat");
			exit(1);
		}
	} else {
		if (S_ISFIFO(stats.st_mode)) {
			if (unlink(fifoName) < 0) {
				perror("Unlink failed");
				exit(1);
			}
		}else {
			printf("Another file with the same name exists.\n");
			exit(1);
		}
	}
	if (mkfifo(fifoName, 0600) < 0) {
		perror("Error on create fifo");
		exit(1);
	}
}

