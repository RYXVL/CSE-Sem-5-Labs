#include <stdio.h>
#include <stdlib.h>

int hits = 0, miss = 0;
int page_count;

int find(int pages[], int request) {
    for(int i=0; i<page_count; i++)
        if(pages[i]==request) return i;
    return -1;
}

int main() {
    int n;
    printf("Enter the number of page requests.\n");
    scanf("%d", &n);

    printf("Enter the number of pages in the main memory: ");
    scanf("%d", &page_count);
    int pages[page_count];
    for(int i=0; i<page_count; i++)
        pages[i] = -1;

    int front = -1, rear = -1, queue[n];
    for(int i=0; i<n; i++)
        queue[i] = -1;

    printf("Please enter the page requests:-\n");
    int request;
    for(int i=0; i<n; i++) {
        scanf("%d", &request);
        if(find(pages, request)>=0)
            hits++;
        else {
            pages[find(pages, queue[++front])] = request;
            queue[++rear] = request;
            miss++;
        }
    }

    printf("Hits: %d\nMiss: %d\n", hits, miss);
    return 0;
}