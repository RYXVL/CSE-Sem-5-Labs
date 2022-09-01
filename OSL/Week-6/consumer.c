#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/msg.h>
#include<unistd.h>
#include<limits.h>
#include<fcntl.h>
#define FIFO_NAME "newpipe"
#define BUFF_SIZE 1000

int main(int argc, char *argv[]) {
    int pipe_fd, res, open_mode = O_RDONLY, n = 0;
    char buff[BUFF_SIZE+1];
    
    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    // int bytes_read = 0;
    if(pipe_fd != -1) {
        while(n<4) {
            printf("%d : ", n+1);
            res = read(pipe_fd, buff, BUFF_SIZE);
            printf("%s\n", buff);
            memset(buff, 0, 1001);
            // bytes_read += BUFF_SIZE;
            n++;
        }
        close(pipe_fd);
    }
}