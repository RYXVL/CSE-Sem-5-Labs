#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
 
int main() {
    pid_t pid;
    pid = fork();
    if(pid == -1)
        printf("Error - Child Process Not Created\n");
    else if(pid == 0) {
        printf("I Am The Child Process\n");
        exit(0);
    }
    else {
        sleep(2);
        printf("Parent Process\n");
    }
    return 0;
}