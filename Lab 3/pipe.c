/*
 ============================================================================
 Name        : pipes.c
 Author      : Paolo Torroni
 Version     :
 Copyright   : Use as you wish
 Description : Template for point 3 in RTSA lab#3
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for pipe
#include <signal.h> // for signals
#include <wait.h> // for wait

void sigpipe_handler(int signo) {
	puts(" -->o Got a SIGPIPE");
}

int compute_sum(int n) {
	int i,sum=0;
	for(i=0;i<n;i++,sum+=i);
	return sum;
}

int main(void) {
	int fd[2], // file descriptors for the pipe:
				   // fd[1] is the write-end of the pipe
				   // fd[0] is the read-end of the pipe
		buf=0, // 1-int-long buffer for parent/child communication
		child_pid; // for the fork system call

	signal(SIGPIPE,sigpipe_handler);

	/* put your code here */

// working with pipes is like working with files

	child_pid=fork();
	if(child_pid<0) {
		perror("Could not fork child");
		exit(1);
	}
	else if(child_pid==0) //child
	{
		/* put your code here */
	}
	else //parent
	{
		/* put your code here */
	}

	return EXIT_SUCCESS;
}
