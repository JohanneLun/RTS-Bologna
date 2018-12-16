#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


pthread_barrier_t barr1;
pthread_barrier_t barr2;

pthread_barrierattr_t attr1;
pthread_barrierattr_t attr2;

unsigned count =  2;

void *f_a(void *arg) {

	puts("!!!First Hello World!!!");
	pthread_barrier_wait(&barr1);
	return NULL;
}

void *f_b(void *arg) {
	pthread_barrier_wait(&barr1);
	puts("!!!Second Hello World!!!");
	pthread_barrier_wait(&barr2);
	return NULL;
}

int main(void) {
	pthread_barrier_init(&barr1, &attr1, count);
	pthread_barrier_init(&barr2, &attr2, count);

	pthread_t thread_a, thread_b;
	pthread_create(&thread_a, NULL, f_a, NULL);
	pthread_create(&thread_b, NULL, f_b, NULL);

	pthread_barrier_wait(&barr2);
	puts("!!!Third Hello World!!!");

	pthread_join(thread_a,NULL);
	pthread_join(thread_b,NULL);

	puts("!!!Last Hello World!!!");
	pthread_barrier_destroy(&barr1);
	pthread_barrier_destroy(&barr2);

	return EXIT_SUCCESS;
}
