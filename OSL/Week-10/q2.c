#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int numSector = 10;
    char sector[1024];
    FILE* diskFptr = fopen(argv[1], "r");
    if(!diskFptr) {
        printf("File not found!\n");
        exit(0);
    }
    fseek(diskFptr, numSector*512, SEEK_SET);
    fread(sector, 1024, 1, diskFptr);
    for(int i=0; i<sizeof(sector); i++) {
        printf("%x", sector[i]);
        if((i+1)%16==0)
            printf("\n");
    }
    fclose(diskFptr);
    return 0;
}