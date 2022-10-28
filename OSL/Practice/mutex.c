#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
int count = 0;

void* test() {
    for(int i=0; i<100; i++) {
        pthread_mutex_lock(&mutex);
        printf("Count: %d\n", ++count);
        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&mutex, 0);
    pthread_create(&t1, 0, test, 0);
    pthread_create(&t2, 0, test, 0);
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    pthread_mutex_destroy(&mutex);
    return 0;
}