#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

int main() {
    char line[200], filename[100];
    printf("Enter the line: ");
    gets(line);
    printf("Enter the filename: ");
    scanf("%s", filename);
    int i = 0;
    while(filename[i]!='\0') i++;
    filename[i] = '.';
    filename[i+1] = 't';
    filename[i+2] = 'x';
    filename[i+3] = 't';
    filename[i+4] = '\0';
    int in = open(filename, O_CREAT|O_WRONLY, S_IRUSR|S_IRGRP|S_IROTH);
    i = 0;
    while(line[i]) {
        write(in, (line+(i++)), 1);
    }
    int out = open(filename, O_RDONLY);
    char c;
    while(read(out, &c, 1)>0) {
        if(c==' ') write(1, "&", 1);
        else write(1, &c, 1);
    }
    return 0;
}
