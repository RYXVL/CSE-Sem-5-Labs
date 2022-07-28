#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    char c[100];
    int i = 0, in;
    if((in=open(argv[2], O_RDONLY)) == -1) {
        write(1, "Error\n", 6);
        exit(0);
    }
    while(read(in, c + i, 1) > 0) {
        while(*(c+i) != '\n') {
            i++;
            read(in, c + i, 1);
        }
        if(strstr(c, argv[1])!=NULL) {
            write(1, c, i);
            write(1, "\n", 1);
        }
        i = 0;
    }
    return 0;
}