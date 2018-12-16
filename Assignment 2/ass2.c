#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>

/***** CONSTANTS AND MACROS *****/
#define N_THREADS 5
#define N_CHOPSTICKS 10
#define FOREVER for(;;)

/***** DEFINITIONS OF NEW DATA TYPES *****/
typedef char thread_name_t[10];
typedef enum {EATING, THINKING, HUNGRY} state_t;
typedef enum {NONE, TWO_LEFT, TWO_RIGHT} chop_choice;

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t philosopher[N_THREADS]; 
    int chopsticks[N_CHOPSTICKS/2];
    chop_choice used_chops[N_CHOPSTICKS/2];
} monitor_t;

/***** GLOBAL VARIABLES *****/
monitor_t mon;

/***** MONITOR API *****/
void pick_up(monitor_t *mon, int id);
void put_down(monitor_t *mon, int id);
void monitor_init(monitor_t *mon);
void monitor_destroy(monitor_t *mon);

/***** OTHER FUNCTION DECLARATIONS *****/
void *philosopher(void *arg);   // thread runner function
double spend_some_time(int);    // wastes some time

void simulate_thinking(int id) {
    printf("%*d: THINKING\n", id*6, id);
    spend_some_time(100);
}
void simulate_eating(int id) {
    printf("%*d: EATING\n", id*6, id);
    spend_some_time(10);
}

/**** IMPLEMENTATION OF MONITOR API *****/
void pick_up(monitor_t *mon, int id) {
    pthread_mutex_lock(&mon->mutex);
    printf("%*d: HUNGRY\n", id*6, id);

    // the index number of the chopstick pairs next to you
    int left_pair = (id+(N_THREADS-1))%N_THREADS;
    int right_pair = id;
    // variables to know the number of the chopsticks next to a philospoher
    int chop_ll = 2*((id+(N_THREADS-1))%N_THREADS);
    int chop_l = 2*((id+(N_THREADS-1))%N_THREADS) + 1;
    int chop_r = 2*id;
    int chop_rr = 2*id + 1;

    while ( !(mon->chopsticks[left_pair] + mon->chopsticks[right_pair] >= 3) ) {
        pthread_cond_wait(&mon->philosopher[id],&mon->mutex);
    }

    if (mon->chopsticks[right_pair] == 2 && mon->chopsticks[left_pair] == 2) {
        long var = rand()%2;
        switch(var) {
            case 0:
                mon->chopsticks[right_pair] = 1;
                mon->chopsticks[left_pair] = 0;
                mon->used_chops[id] = TWO_LEFT;
                printf("%*d: Picked up chopstick %d, %d and %d\n", id*6, id, chop_ll, chop_l, chop_r);
                break;
            case 1: 
                mon->chopsticks[right_pair] = 0;
                mon->chopsticks[left_pair] = 1;
                mon->used_chops[id] = TWO_RIGHT;
                printf("%*d: Picked up chopstick %d, %d and %d\n", id*6, id, chop_l, chop_r, chop_rr);
                break;
        } 
    }
    else if (mon->chopsticks[right_pair] == 1 && mon->chopsticks[left_pair] == 2) {
        mon->chopsticks[right_pair] = 0;
        mon->chopsticks[left_pair] = 0;
        mon->used_chops[id] = TWO_LEFT;
        printf("%*d: Picked up chopstick %d, %d and %d\n", id*6, id, chop_ll, chop_l, chop_r);
    }
    else if(mon->chopsticks[right_pair] == 2 && mon->chopsticks[left_pair] == 1) {
        mon->chopsticks[right_pair] = 0;
        mon->chopsticks[left_pair] = 0;
        mon->used_chops[id] = TWO_RIGHT;
        printf("%*d: Picked up chopstick %d, %d and %d\n", id*6, id, chop_l, chop_r, chop_rr);
    }
    else {
        printf("%*d: ERROR - Sum chopsticks left and right less than 3\n", id*6, id);
    }
    pthread_mutex_unlock(&mon->mutex);
}

void put_down(monitor_t *mon, int id) {
    pthread_mutex_lock(&mon->mutex);

    // the index number of the chopstick pairs next to you
    int left_pair = (id+(N_THREADS-1))%N_THREADS;
    int right_pair = id;
    // the index number of philosopher next to you
    int left_phil = (id+(N_THREADS-1))%N_THREADS;
    int right_phil = id+1;
    // variables to know the number of the chopsticks next to a philospoher
    int chop_ll = 2*((id+(N_THREADS-1))%N_THREADS);
    int chop_l = 2*((id+(N_THREADS-1))%N_THREADS) + 1;
    int chop_r = 2*id;
    int chop_rr = 2*id + 1;

    chop_choice mode = mon->used_chops[id];
    switch (mode) {
        case NONE:
            printf("%*d: ERROR - No chopsticks to put down.\n", id*6, id);
            printf("%*d: Chopsticks to the left: %d\tChopsticks to the right: %d\n", id*6, id, mon->chopsticks[left_pair], mon->chopsticks[right_pair] );
            break;
        case TWO_LEFT:
            mon->chopsticks[left_pair] = 2;
            if (mon->chopsticks[right_pair] < 2 ) {
                mon->chopsticks[right_pair]++;
            }
            printf("%*d: Put down chopsticks %d, %d and %d\n", id*6, id, chop_ll, chop_l, chop_r);
            pthread_cond_signal(&(mon->philosopher[left_phil]));
            pthread_cond_signal(&(mon->philosopher[right_phil]));
            break;
        case TWO_RIGHT:
            if (mon->chopsticks[left_pair] < 2 ) {
                mon->chopsticks[left_pair]++;
            }            
            mon->chopsticks[right_pair] = 2;
            printf("%*d: Put down chopsticks %d, %d and %d\n", id*6, id, chop_l, chop_r, chop_rr);
            pthread_cond_signal(&(mon->philosopher[left_phil]));
            pthread_cond_signal(&(mon->philosopher[right_phil]));
            break;
        default:
            printf("%*d: ERROR - Something fucked up!\n", id*6, id);
            break;
    }
    mon->used_chops[id] = NONE;
    pthread_mutex_unlock(&mon->mutex);
}

void monitor_init(monitor_t *mon) {
    pthread_mutex_init(&mon->mutex,NULL);
    for(int i = 0; i < N_THREADS; i++) {
        pthread_cond_init(&mon->philosopher[i],NULL);
        mon->chopsticks[i] = 2;
    }
}

void monitor_destroy(monitor_t *mon) {
    for (int i = 0; i < N_THREADS; i++) {
        pthread_cond_destroy(&mon->philosopher[i]);
        mon->chopsticks[i] = 0;
    }
    pthread_mutex_destroy(&mon->mutex);
}

int main(void) {
    // thread management data structures
    pthread_t my_threads[N_THREADS];
    thread_name_t my_thread_names[N_THREADS];
    int i;

    monitor_init(&mon);

    for (i = 0; i < N_THREADS; i++) {
        sprintf(my_thread_names[i],"%d",i);
        pthread_create(&my_threads[i], NULL, philosopher, my_thread_names[i]);
    }
    for (i = 0; i < N_THREADS; i++) {
        pthread_join(my_threads[i], NULL);
    }
    monitor_destroy(&mon);
    return EXIT_SUCCESS;
}

/***** HELPER FUNTIONS *****/
void *philosopher(void *arg) {
    // local variables definition and initialization
    char *thread_name = arg;
    int id = atoi(arg);
    FOREVER {
        simulate_thinking(id);
        pick_up(&mon, id);
        simulate_eating(id);
        put_down(&mon, id);
    }
    pthread_exit(NULL);
}

double spend_some_time(int max_steps) {
    double x, sum=0.0, step;
    long i, N_STEPS=rand()%(max_steps*1000000);
    step = 1/(double)N_STEPS;
    for(i=0; i<N_STEPS; i++) {
        x = (i+0.5)*step;
        sum+=4.0/(1.0+x*x);
    }
    return step*sum;
}