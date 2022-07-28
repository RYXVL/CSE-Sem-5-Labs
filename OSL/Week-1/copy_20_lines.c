#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    char c[100], key;
    int in, i = 0, count = 0;
    in = open(argv[1], O_RDONLY);
    if(in == -1) {
        write(1, "Error\n", 6);
        exit(0);
    }
    while(1) {
        while(read(in, c+i, 1) > 0 && count < 20) {
            while(c[i]!='\n') {
                i++;
                read(in, c+i, 1);
            }
            count++;
            write(1, c, i+1);
            i = 0;
            memset(c, 0, 100);
        }
        if(count!=20) exit(0);
        count = 0;
        read(0, &key, 1);
        if(key == 'q') exit(0);
        memset(&key, 0, 1);
    }
    return 0;
}