#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

pid_t child_pid;

int main(void) {

	child_pid=fork();
	if(child_pid==0) {
    printf("Child PID: %d \n", getpid());
		return 0;
	}
	else if(child_pid>0) {
    wait(0);
		printf("Parent PID: %d \n", getpid());
		return 0;
	}
	else {
		perror("fork() error\n");
		return 1;
	}
}
