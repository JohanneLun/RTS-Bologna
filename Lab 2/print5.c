#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

pid_t child_pid;
int wstatus;

int main(void) {
  int x = 0;
  printf("Initial value of x = %d\n", x);

	child_pid=fork();

	if(child_pid==0) {
    x = 5;
    printf("Child: Value of x = %d\n", x);
		return x;
	}
	else if(child_pid>0) {
    wait(&wstatus);
    if (WIFEXITED(wstatus)) {
      x = WEXITSTATUS(wstatus);
    }
		printf("Parent: wstatus %d is and Value of x = %d\n", wstatus, x);
		return 0;
	}
	else {
		perror("fork() error\n");
		return 1;
	}
}
