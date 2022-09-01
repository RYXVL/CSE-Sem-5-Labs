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
            fprintf(stderr, "Could not create file pipe%s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }
    printf("Program 1 communication with Program 2\n");
    while(1) {
        pipe_fd = open(FIFO_NAME, open_mode2);
        res = read(pipe_fd, buff, BUFF_SIZE);
        if(strstr(buff, "exit") != NULL) break;
        printf("\nText from the Program 2: ");
        printf("%s\n", buff);
        close(pipe_fd);
        pipe_fd = open(FIFO_NAME, open_mode1);
        printf("\nEnter the text to send to Program 2: ");
        fgets(buff, BUFF_SIZE, stdin);
        res = write(pipe_fd, buff, BUFF_SIZE);
        close(pipe_fd);
        if(strstr(buff, "exit") != NULL) break;
    }
    close(pipe_fd);
    printf("Process %d finished.\n", getpid());
    exit(EXIT_SUCCESS);
}