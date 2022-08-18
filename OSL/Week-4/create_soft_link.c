#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Insufficient number of arguments.\n");
        exit(0);
    }
    char *oldpath = argv[1];
    char *newpath = argv[2];
    struct stat status;
    if(stat(oldpath, &status)!=0) {
        printf("Status Retrieval Failed.\n");
        exit(0);
    }
    printf("\nFile list before linking the new link.\n");
    system("ls");
    printf("Number of links to oldpath before new link: %ld\n\n", status.st_nlink);
    symlink(oldpath, newpath);
    printf("File list after linking the new link.\n");
    system("ls");
    if(stat(oldpath, &status)!=0) {
        printf("Status Retrieval Failed.\n");
        exit(0);
    }
    printf("Number of links to oldpath after new link: %ld\n\n", status.st_nlink);
    unlink(newpath);
    printf("File list after unlinking the new link.\n");
    system("ls");
    if(stat(oldpath, &status)!=0) {
        printf("Status Retrieval Failed.\n");
        exit(0);
    }
    printf("Number of links to oldpath after unlinking newpath: %ld\n", status.st_nlink);
    return 0;
}