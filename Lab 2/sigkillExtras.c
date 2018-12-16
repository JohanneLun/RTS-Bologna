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
	signal(SIGUSR2, loop_breaker);
	printf("To change color, kill -%d %d\n", SIGUSR1, getpid());
	printf("To halt, kill -%d %d\n", SIGUSR2, getpid());
	FOREVER {
		sleep(2);
		if(x==0){
			puts("green");
		}
		else if (x>0){
			puts("blue");
		}
		if (x < 0){
			return 0;
		}
	}
	return EXIT_SUCCESS;
}

void loop_breaker(int signum) {
	/* your code here */
	if (signum == SIGUSR1){
		x = 1-x;
		puts ("Changing color");
	}
	else if (signum == SIGUSR2){
		x = -1;
		puts("Terminating...");
	}
}