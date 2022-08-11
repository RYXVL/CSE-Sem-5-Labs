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
        printf("Error - Child Process Not Created\n");
    else if(pid == 0) {
        printf("I Am The Child Process\n");
        execlp("./ip","./",NULL);
        exit(0);
    }
    else {
        printf("I am The Parent Process\n");
        wait(NULL);
        printf("Child Returned\n");
    }
    return 0;
}