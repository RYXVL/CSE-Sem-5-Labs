#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Insufficient number of arguments.\n");
        exit(0);
    }
    struct stat status;
    if(stat(argv[1], &status)!=0) {
        printf("Status Retrieval Failed.\n");
        exit(0);
    }
    printf("Inode Number of %s is %ld.", argv[1], status.st_ino);
    return 0;
}
