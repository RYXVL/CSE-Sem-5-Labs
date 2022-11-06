#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* sum(void *arr) {
    int* newarr = (int*)arr;
    int n = newarr[0];
    int* sum = (int*)malloc(sizeof(int));
    *sum = 0;
    for(int i=1; i<=n; i++)
        (*sum)+=newarr[i];
    return (void*)sum;
}

void* rev(void *arr) {
    int* newarr = (int*)arr;
    int n = newarr[0];
    for(int i=1; i<=n; i++) 
    newarr[i]*=2;
}

int main() {
    pthread_t thread1, thread2;

    int n;
    printf("Enter the length of the array: ");
    scanf("%d", &n);

    int arr[n+1];
    arr[0] = n;
    printf("Enter the elements of the array: ");
    for(int i=1; i<=n; i++)
        scanf("%d", &arr[i]);

    pthread_create(&thread1, 0, sum, (void*)arr);
    pthread_create(&thread2, 0, rev, (void*)arr);

    int *res;
    pthread_join(thread1, (void**)&res);
    pthread_join(thread2, 0);

    printf("The sum of elements is: %d", *res);
    printf("The reversed array is: ");
    for(int i=1; i<=n; i++)
        printf("%d ", arr[i]);

    return 0;
}