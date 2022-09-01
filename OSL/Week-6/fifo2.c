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
#define BUFF_SIZE 10000

int main(int argc, char const *argv[]) {
    int pipe_fd, res, open_mode1 = O_WRONLY, open_mode2 = O_RDONLY, n = 0;
    char buff[BUFF_SIZE+1];
    if(access(FIFO_NAME, F_OK) == -1) {
        res = mkfifo(FIFO_NAME, 0777);
        if(res != 0) {
            fprintf(stderr, "Could not create files%s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }
    printf("Program 2 communication with Program 1\n");
    while(1) {
        pipe_fd = open(FIFO_NAME, open_mode1);
        printf("\nTo Program 1: ");
        scanf("%s", buff);
        res = write(pipe_fd, buff, BUFF_SIZE);
        close(pipe_fd);
        if(strstr(buff, "exit") != NULL) break;
        pipe_fd = open(FIFO_NAME, open_mode2);
        res = read(pipe_fd, buff, BUFF_SIZE);
        if(strstr(buff, "exit") != NULL) break;
        printf("\nFrom Program 1: ");
        printf("%s\n", buff);
        close(pipe_fd);
    }
    close(pipe_fd);
    printf("Process %d finished.\n", getpid());
    exit(EXIT_SUCCESS);
}