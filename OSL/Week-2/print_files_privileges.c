#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

char const *perms(__mode_t mode)
{
    static char local_buff[9] = {0};
    int i = 0;
    local_buff[i++] = ((mode & S_IRUSR) ? 'r' : '-');
    local_buff[i++] = ((mode & S_IWUSR) ? 'w' : '-');
    local_buff[i++] = ((mode & S_IXUSR) ? 'x' : '-');
    local_buff[i++] = ((mode & S_IRGRP) ? 'r' : '-');
    local_buff[i++] = ((mode & S_IWGRP) ? 'w' : '-');
    local_buff[i++] = ((mode & S_IXGRP) ? 'x' : '-');
    local_buff[i++] = ((mode & S_IROTH) ? 'r' : '-');
    local_buff[i++] = ((mode & S_IWOTH) ? 'w' : '-');
    local_buff[i++] = ((mode & S_IXOTH) ? 'x' : '-');
    return local_buff;
}

void printdir(char *dir, int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp=opendir(dir))==NULL) {
        fprintf(stderr, "cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while ((entry = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            if(strcmp(".", entry->d_name)==0 || strcmp("..", entry->d_name)==0) continue;
            printf("%*s%s\n", depth, " ", entry->d_name);
            printf("%s", perms(statbuf.st_mode));
            printdir(entry->d_name, depth+2);
        }
        else {
            printf("%*s%s\n", depth, "", entry->d_name);
        printf("%s", perms(statbuf.st_mode));
        }
    }
    chdir("..");
    closedir(dp);
}

int main(int argc, char *argv[]) {
    printdir(argv[1], 0);
    return 0;
}
