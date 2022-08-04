#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>

void printdir(char *dir, int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp=opendir(dir))==NULL) {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry=readdir(dp))!=NULL) {
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            if(strcmp(".", entry->d_name)==0 || strcmp("..", entry->d_name)==0) continue;
            printdir(entry->d_name, depth+2);
        }
        else printf("%*s%s\n", depth, "", entry->d_name);
    }
    chdir("..");
    closedir(dp);
}

int main(int argc, char *argv[]) {
    printdir(argv[1], 0);
    return 0;
}
