#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/wait.h>
 
int main() {
    pid_t pid;
    pid = fork();
    if(pid == -1)
        printf("Error: Child Process Not Created\n");
    else if(pid == 0) {
        printf("In Child Process\n");
        printf("C PID = %d\n",getpid());
        printf("C Parent PID = %d\n",getppid());
        printf("C Child PID = %d\n",pid);
    }
    else {
        printf("\nIn The Parent Process\n");
        wait(NULL);
        printf("P PID = %d\n",getpid());
        printf("P Parent PID = %d\n",getppid());
        printf("P Child PID = %d\n",pid);
    }
    return 0;
}