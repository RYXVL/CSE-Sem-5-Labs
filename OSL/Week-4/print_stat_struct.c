#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

char const *perms(__mode_t mode) {
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
    printf("File Name: %s\nDevice Container ID: %ld\nInode Number: %ld\nMode Permissions: %10.10s\nNumber of Hard Links: %ld\nUser ID: %d\nGroup ID: %d\nDevice ID: %ld\nTotal Size: %ld\nBlock Size: %ld\nNumber of blocks: %ld\nLast Access Time: %sLast Modified Time: %sLast Status Change Time: %s", argv[1], status.st_ino, status.st_dev, perms(status.st_mode),status.st_nlink, status.st_uid, status.st_gid, status.st_rdev, status.st_size, status.st_blksize, status.st_blocks, ctime(&status.st_atime), ctime(&status.st_mtime), ctime(&status.st_ctime));
    return 0;
}