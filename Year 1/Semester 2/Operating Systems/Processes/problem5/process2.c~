#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main() {
	int fd, dim, k, i;
	char* buf = (char*)malloc(sizeof(char) * SIZE);
	memset(buf, 0, SIZE * sizeof(char));
	if ((fd = open(myfifo, O_RDONLY)) < 0) {
		perror("Error on open fifo");
		exit(1);
	}

	while (1) {
		if (read(fd, &dim, sizeof(int)) < 0) {
			perror("Error on read size from fifo");
		}
		if (dim < 0) {
			printf("Process ended. Goodbly!\n");
			break;
		}
		i = 0;
		while (i < dim) {
			int size;
			if (dim - i > SIZE - 1) {
				size = SIZE - 1;
			}else {
				size = dim - i;
			}
			if ((k = read(fd, buf, size)) < 0) {
				perror("Error on read message from fifo");
			}else {
				i += k;
				printf("%s", buf);
				memset(buf, 0, SIZE * sizeof(char));
			}
		}
		fflush(stdout);
	}
	free(buf);
	close(fd);
	return 0;
}
