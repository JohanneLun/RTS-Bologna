/*
 ============================================================================
 Name        : fifo.c
 Author      : Paolo Torroni
 Version     :
 Copyright   : Use as you wish
 Description : Template for point 4 in RTSA lab#3 (Program1)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // for mkfifo
#include <sys/stat.h> // for mkfifo
#include <fcntl.h> // for mode argument in mkfifo
#include <unistd.h> // for write

int compute_sum(int n) {
	int i,sum=0;
	for(i=0;i<n;i++,sum+=i);
	return sum;
}

int main(int argc, char *argv[]) {
	int fd, n, buf=compute_sum(10), created_fifo;
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
