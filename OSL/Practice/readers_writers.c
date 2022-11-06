#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int data = 1;
int reader_count = 0;
pthread_mutex_t mut, wr;

void* writer() {
    pthread_mutex_lock(&mut);
    data*=2;
    printf("New value of data %d\n", data);
    pthread_mutex_unlock(&mut);
}

void* reader() {
    if(!reader_count)
        pthread_mutex_lock(&mut);

    pthread_mutex_lock(&wr);
    reader_count++;
    pthread_mutex_unlock(&wr);

    printf("Read value is %d\n", data);

    pthread_mutex_lock(&wr);
    reader_count--;
    pthread_mutex_unlock(&wr);

    if(reader_count==0)
        pthread_mutex_unlock(&mut);
}

int main() {
    pthread_mutex_init(&mut, 0);
    pthread_mutex_init(&wr, 0);

    pthread_t thread[10];
    for(int i=0; i<3; i++)
        pthread_create(&thread[i], 0, writer, 0);
    for(int i=3; i<10; i++)
        pthread_create(&thread[i], 0, reader, 0);
    for(int i=0; i<10; i++)
        pthread_join(thread[i], 0);
    return 0;
}