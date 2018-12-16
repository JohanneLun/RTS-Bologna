#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;
sem_t sem2;

void *f_a(void *arg) {
	puts("!!!First Hello World!!!");
	sem_post(&sem);
	return NULL;
}

void *f_b(void *arg) {
	sem_wait(&sem);
	puts("!!!Second Hello World!!!");
	sem_post(&sem2);
	return NULL;
}

int main(void) {
	sem_init(&sem, 0, 0);
	sem_init(&sem2, 0, 0);

	pthread_t thread_a, thread_b;

	pthread_create(&thread_a, NULL, f_a, NULL);
	pthread_create(&thread_b, NULL, f_b, NULL);

	sem_wait(&sem2);
	puts("!!!Third Hello World!!!");
	pthread_join(thread_a,NULL);
	pthread_join(thread_b,NULL);
	puts("!!!Last Hello World!!!");

	sem_destroy(&sem);
	return EXIT_SUCCESS;
}
