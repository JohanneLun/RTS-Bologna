/*
 ============================================================================
 Name        : fifo2.c
 Author      : Paolo Torroni
 Version     :
 Copyright   : Use as you wish
 Description : Template for point 4 in RTSA lab#3 (Program2)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // for mkfifo
#include <sys/stat.h> // for mkfifo
#include <fcntl.h> // for mode argument in mkfifo
#include <unistd.h> // for write

int main(int argc, char *argv[]) {
	int fd, n, buf, created_fifo;
	if(argc<2) {
		printf("Usage: %s <pipename>\n",argv[0]);
		exit(1);
	}
	if(created_fifo=mkfifo(argv[1],S_IRUSR | S_IWUSR)) {
		perror("Could not create FIFO");
	}

	/* write your code here */

	if(!created_fifo)
		unlink(argv[1]);
	return EXIT_SUCCESS;
}
