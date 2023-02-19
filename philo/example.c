#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

typedef struct {
  int id;
  pthread_mutex_t *left_fork;
  pthread_mutex_t *right_fork;
} philo;

void *routine(void *arg) {
  philo *p = (philo *)arg;
  while (1) {
    // philosopher thinks
    printf("Philosopher %d is thinking\n", p->id);
    // philosopher picks up left fork
    pthread_mutex_lock(p->left_fork);
    printf("Philosopher %d picks up left fork\n", p->id);

    // philosopher picks up right fork
    pthread_mutex_lock(p->right_fork);
    printf("Philosopher %d picks up right fork\n", p->id);

    // philosopher eats
    printf("Philosopher %d is eating\n", p->id);
    sleep(1);

    // philosopher puts down right fork
    pthread_mutex_unlock(p->right_fork);
    printf("Philosopher %d puts down right fork\n", p->id);

    // philosopher puts down left fork
    pthread_mutex_unlock(p->left_fork);
    printf("Philosopher %d puts down left fork\n", p->id);

    // philosopher sleeps
    printf("Philosopher %d is sleeping\n", p->id);
    sleep(1);
  }
}

int main() {
  pthread_t threads[NUM_PHILOSOPHERS];
  pthread_mutex_t forks[NUM_PHILOSOPHERS];
  philo philos[NUM_PHILOSOPHERS];
  int i;
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_mutex_init(&forks[i], NULL);
  }
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    philos[i].id = i;
    philos[i].left_fork = &forks[i];
    philos[i].right_fork = &forks[(i + 1) % NUM_PHILOSOPHERS];
    pthread_create(&threads[i], NULL, routine, (void *)&philos[i]);
  }
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(threads[i], NULL);
  }
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_mutex_destroy(&forks[i]);
  }
  return 0;
}
