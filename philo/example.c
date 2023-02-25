#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define EAT_TIME_MS 5000 // 5 seconds

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int id = *((int*)arg);
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    int has_eaten = 0;
    while (1) {
        // Think for a while
        printf("Philosopher %d is thinking\n", id);
        sleep(rand() % 5);

        // Pick up left fork
        pthread_mutex_lock(&forks[left_fork]);
        printf("Philosopher %d picked up left fork %d\n", id, left_fork);

        // Pick up right fork
        pthread_mutex_lock(&forks[right_fork]);
        printf("Philosopher %d picked up right fork %d\n", id, right_fork);

        // Eat for a while
        printf("Philosopher %d is eating\n", id);
        usleep(1 * 1000);
        has_eaten = 1;

        // Put down right fork
        pthread_mutex_unlock(&forks[right_fork]);
        printf("Philosopher %d put down right fork %d\n", id, right_fork);

        // Put down left fork
        pthread_mutex_unlock(&forks[left_fork]);
        printf("Philosopher %d put down left fork %d\n", id, left_fork);

        // Check if philosopher has eaten for long enough
        if (has_eaten || (rand() % 2 == 0)) {
            printf("Philosopher %d has finished eating and died\n", id);
            return NULL;
        }
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Start philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Sleep for 200 ms before checking if any philosophers have died
    usleep(200000);

    // Check if any philosophers have died
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        void* result;
        pthread_join(philosophers[i], &result);
    }

    // Clean up mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
