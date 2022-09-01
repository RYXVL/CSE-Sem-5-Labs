#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>

int main(int argc, char const *argv[]) {
    int n, fd[2];
    char buff[1024];
    char *msg = "Omega Clearance";
    pipe(fd);
    write(fd[1], msg, strlen(msg));
    n = read(fd[0], buff, 1024);
    if(n >= 0) printf("%d bytes read from the pipe and msg is: %s", n, buff);
    else perror("Read");
    exit(0);
}