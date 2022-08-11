#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <errno.h>
#include<sys/types.h>
#include<sys/wait.h>
 
int main() {
    int status;
    pid_t pid;
    pid = fork();
    if(pid == -1)
        printf("Error - Child Process Not Created\n");
    else if(pid == 0) {
        printf("I Am The Child Process\n");
        exit(0);
    }
    else {
        printf("I am The Parent Process\n");
        wait(&status);
        printf("Child Returned: %d\n",status);
    }
    return 0;
}
