/*
 ============================================================================
 Name        : 2017-10-18-linux-signals.c
 Author      : Paolo Torroni
 Version     :
 Copyright   : Use as you wish
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define FOREVER for(;;)

int x;

void loop_breaker(int signo) {
	/* your code here */

	puts("awww");
}

int main(void) {
	/* your code here */

	printf("To halt, kill -%d %d\n", SIGUSR1, getpid());
	FOREVER {
    printf("x = %d\n", x);
		sleep(1);
		if(x==0)
			puts("green");
		else if (x>0)
			puts("blue");
    if(x>=0)
			x=1-x;
    else{
      printf("x = %d\n", x);
      return EXIT_SUCCESS; // same as exit(0)
    }
	}
	return EXIT_SUCCESS;
}
