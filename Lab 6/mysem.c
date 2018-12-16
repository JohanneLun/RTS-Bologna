/*
 * mysem-template.c
 *
 *  Created on: Nov 17, 2017
 *      Author: Paolo Torroni
 *      Template for semaphore implementation using condvars
 */

#include "mysem.h"

int sem_init(sem_t *sem, int pshared, unsigned int value) {
	/* INSERT YOUR CODE HERE */
	sem->value = value;
	pthread_mutex_init(&sem->m, NULL);
	pthread_cond_init(&sem->list, NULL);
	return 0;
}

int sem_destroy(sem_t *sem){
	/* INSERT YOUR CODE HERE */
	pthread_mutex_destroy(&sem->m);
	pthread_cond_destroy(&sem->list);
	return 0;
}

int sem_wait(sem_t *sem){
	/* INSERT YOUR CODE HERE */
	pthread_mutex_lock(&sem->m);
	s->value--;
	s->n_w++;
	while(s->value < 0) {
		pthread_cond_wait(&sem->list, &sem->m);
	}
	s->n_w--;
	pthread_mutex_unlock(&sem->m);
	return 0;
}

int sem_post(sem_t *sem){
	/* INSERT YOUR CODE HERE */
	pthread_mutex_lock(&sem->m);
	s->value++;
	if (s->n_w > 0){
		pthread_cond_signal(&sem->list);
	}
	pthread_mutex_unlock(&sem->m);
	return 0;
}
