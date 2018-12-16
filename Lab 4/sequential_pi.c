#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define N_STEPS (long int) 1000000

int i;
double pi, x, sum = 0.0; /* this data is shared by the thread(s) */
double step = 1/(double)N_STEPS;
void *runner(void *param); /* the thread */

int main(void) {
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */

	for(i=0; i<N_STEPS; i++) {
		char arg[10]; sprintf(arg,"%d",i); /* in the book, this value is taken from command line */
		pthread_attr_init(&attr);
		pthread_create(&tid,&attr,runner,arg);
		pthread_join(tid,NULL);
	}
	printf("Pi = %f\n", pi);
	return EXIT_SUCCESS;
}

// The thread will begin control in this function
void *runner(void *param){
	i = atoi(param);
	x = (i+0.5)*step;
	sum+=4.0/(1.0+x*x);
	pi=step*sum;

	pthread_exit(0);
}
