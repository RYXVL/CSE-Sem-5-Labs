#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t semaphore;
int val;

void* func1() {
    printf("Thread 1\n");
    sem_post(&semaphore);
    sem_getvalue(&semaphore, &val);
}

void* func2() {
    sem_wait(&semaphore);
    printf("Thread 2\n");
}

int main() {
    pthread_t threads[2];
    sem_init(&semaphore, 0, 1);
    pthread_create(&threads[0], 0, func1, 0);
    pthread_create(&threads[1], 0, func2, 0);
    pthread_join(threads[0], 0);
    pthread_join(threads[1], 0);
    sem_destroy(&semaphore);
}
