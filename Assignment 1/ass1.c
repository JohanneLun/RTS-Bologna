/*
 ============================================================================
 Name        : 2018-assignment-1-template.c
 Author      : Paolo Torroni
 Version     :
 Copyright   : For personal use only
 Description : Template for RTSA-M's first assignment, fall 2018
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>

#define FOREVER while(!time_ended)
#define N_THREADS 10
#define PREFIX "cart-"
/* the following values are just examples of the possible duration
 * of each action and of the simulation: feel free to change them */
#define MAX_DELAY_PLACE_BOX 2
#define MAX_DELAY_PICK_UP_BOX 10
#define MAX_DELAY_UNLOAD_BOX 1
#define MAX_DELAY_BRING_BOX_BACK 12
#define END_OF_TIME 60
#define TRUE 1
#define FALSE 0

typedef char name_t[20];
typedef int boolean;
time_t big_bang;
boolean time_ended=FALSE;
int num_box, count_placed, count_returned = 0;

sem_t sem;
sem_t returned;

//sem_post(&sem);
//sem_wait(&sem);

void do_action(char *thread_name, char *action_name, int max_delay) {
	int delay=rand()%max_delay+1;
	printf("[%4.0f]\t%s: %s (%d) started\n", difftime(time(NULL),big_bang), thread_name, action_name, delay);
	
	if (thread_name == "fork lift") {
		printf("forklift place\n");
		sem_wait(&sem);
		num_box--;
		count_placed++;
		sem_post(&sem);
	}
	else if(action_name == "unload box") {
		printf("cart unload\n");
		num_box++;
		sem_post(&sem);
	}
	else {
		sem_wait(&returned);
		count_returned++;
		sem_post(&returned);
	}
	sleep(delay);
	printf("[%4.0f]\t%s: %s (%d) ended\n", difftime(time(NULL),big_bang), thread_name, action_name, delay);
}

void *forklift(void *arg) {
	FOREVER {
		if (num_box > 0){
			do_action("fork lift", "place box and return to alley", MAX_DELAY_PLACE_BOX);
		}
	}
	puts("Terminating fork lift.");
	pthread_exit(NULL);
}

void *cart(void *thread_name) {
	int id=atoi(thread_name+strlen(PREFIX));
	FOREVER {
		do_action(thread_name, "pick up box and go to alley", MAX_DELAY_PICK_UP_BOX);

		sem_wait(&sem);
		if(num_box < 5){
			do_action(thread_name, "unload box", MAX_DELAY_UNLOAD_BOX);
		}
		else{
			do_action(thread_name, "bring box back", MAX_DELAY_BRING_BOX_BACK);
		}
		sem_post(&sem);
	}
	printf("Terminating cart %d.\n", id);
	pthread_exit(NULL);
}

int main(void) {
	sem_init(&sem, 0, 1);
	sem_init(&returned, 0, 1);

	pthread_t fork_id, cart_id[N_THREADS];
	name_t cart_name[N_THREADS];
	time(&big_bang);

	pthread_create(&fork_id, NULL, forklift, NULL);
	for(int i=0;i<N_THREADS;i++) {
		sprintf(cart_name[i],"%s%d", PREFIX, i);
		pthread_create(cart_id+i,NULL,cart,cart_name+i);
	}
	sleep(END_OF_TIME);
	time_ended=TRUE;

	pthread_join(fork_id,NULL);
	for(int i=0;i<N_THREADS;i++) {
		pthread_join(cart_id[i],NULL);
	}

	printf("Number of boxes placed: %d\nNumber of boxes returned: %d",count_placed, count_returned);
	sem_destroy(&sem);
	sem_destroy(&returned);
	return EXIT_SUCCESS;
}
