/**
 * Sample thread program
 *
 * [Adapted from the textbook's course material]
 * [Download all source code of the examples in the book from
 *   http://people.westminstercollege.edu/faculty/ggagne/osc/final-src-osc9e.zip]
 *
 * This is a pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 *
 * To compile this program from command line interface:
 * gcc thrd.c -lpthread
 *
 * Figure 4.9
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define N_STEPS (long int) 1000000000
#define N_THREADS 6

double pi_final; /* this data is shared by the thread(s) */
typedef char tname_t[5];

int compute_pi(int interval, int N) {

	int i;
	double pi, step, x, sum=0.0;

	step =  1/(double)N_STEPS;

	for(i=(N_STEPS/N)*interval; i<(N_STEPS/N)*(interval+1); i++) {
		x = (i+0.5)*step;
		sum=4.0/(1.0+x*x); //removed a plus from sum+=

		//moved these two lines here for the race condition task
		pi=step*sum;
		pi_final+=pi;
	}


	printf("compute_pi(%i,%i): pi = %f,\tpi_final = %f\n", interval, N, pi, pi_final);
	return EXIT_SUCCESS;
}

void *runner(void *param); /* the thread */

int main(int argc, char *argv[]) {
	int tn; // thread_number
	tname_t arg[5]; // thread name
	pthread_t tid[N_THREADS]; /* the thread identifiers */
	pthread_attr_t attr[N_THREADS]; /* set of attributes for the thread */

	struct timespec tv_start, tv_end;
	clock_gettime(CLOCK_REALTIME,&tv_start);

	/* get the default attributes */
	for(tn=0;tn<N_THREADS;tn++)
		pthread_attr_init(&attr[tn]);

	/* create the threads */
	for(tn=0;tn<N_THREADS;tn++) {
		sprintf(arg[tn],"%d\n",tn);
		pthread_create(&tid[tn],&attr[tn],runner,arg[tn]);
	}

	puts("I am parent");


	/* now wait for the thread to exit */
	for(tn=0;tn<N_THREADS;tn++)
		pthread_join(tid[tn],NULL);

	clock_gettime(CLOCK_REALTIME,&tv_end);
	printf("parent:\t pi_final = %.10f\n",pi_final);
	printf("parent:\t actual PI: %.10f\n", M_PI);
	printf("parent:\t N_THREADS: %d, N_STEPS: %.0e, total time: %.3f (msec)\n", N_THREADS, (double) N_STEPS, (tv_end.tv_nsec-tv_start.tv_nsec + 1e9 * (tv_end.tv_sec-tv_start.tv_sec))/(double)1e6);
	return EXIT_SUCCESS;
}

// The thread will begin control in this function
void *runner(void *param) {
	printf("I am thread %s", (char *) param);
	compute_pi(atoi(param),N_THREADS);
	pthread_exit(0);
}



/* Task 1.3
I am running on a virtual machine on a Macbook Air
With 10 threads, and 1.000.000.000 steps, I got a segmentation fault (core dumped).
The same happened with 8, but with 7 and down the programme runs. They all run for around 30 sec.
With 7 and 6 there was a error on the 8th decimanl of pi. So it seems that more thread isnt neccessarily better.

With 7 threads and 1.000.000 steps, the time was 79 ms but there was an error on the 6th decimal of pi.
When running the same numbers some more times the time it took was down to 49 ms on the last run.

With 4 threads and 1.000.000 steps, the time was only 46 ms and the actual pi and final pi were exactly the same
With 2 threads the time was 82 ms. But pi was correct.

With 4 threads and 1000 steps pi had an error on the 7th decimal.
With 7 threads and 1000 steps pi had an error on the 2nd decimal.

The fastest while correct was 10.000 steps and 4 htreads. It took 7.4 ms.

From this it seems that more threads often takes longer and is more inaccurate.
I know that my amc has a dual core i5, but i cannot find anything that implies that from the task manager.
When running with 1 to 6 threads and 1.000.000.000 steps it takes around 30 sec for all. They all use 100% of the cPU.
But when I turn down the steps to 1.000.000 they are still equally fast, but dont use anywhere near 100% of the CPU.

Of course all these errors can be caused by threads that doesnt have access to a correct value becuase of for example race conditions.
*/


/* Task 1.4
When running some of the prints saying "computing" of "I am .. " did not come in the right order. when running 5 threads the order they outputted in one case was 4,3,1,2,0.

This can be fixed with semaphores or mutexes.


*/
