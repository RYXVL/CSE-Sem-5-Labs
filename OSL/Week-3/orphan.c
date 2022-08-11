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
        printf("Parent PID Before = %d\n",getppid());
        sleep(5);
        printf("Parent PID After = %d\n",getppid());
        exit(0);
    }
    else
        printf("Parent Process\n");
    return 0;
}