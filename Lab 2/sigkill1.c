#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define FOREVER for(;;)

int x = 0;
int child_pid;
int status = 0;

void loop_breaker(int);

int main(void) {
	/* your code here */
	signal(SIGUSR1, loop_breaker);
	printf("To halt, kill -%d %d\n", SIGUSR1, getpid());
	FOREVER {
		sleep(2);
		if(x==0){
			puts("green");
		}
		else if (x>0){
			puts("blue");
		}
		if(x>=0){
			x=1-x;
		}
		if (x < 0){
			puts("Terminating...");
			return 0;
		}
	}
	return EXIT_SUCCESS;
}

void loop_breaker(int signum) {
	/* your code here */
	x = -1;
	//exit(0);
	//puts("awww");
}