#include <stdio.h>
#include <stdlib.h>

int main() {
    int blockSize[5] = {100, 500, 200, 300, 600};
    int processSize[4] = {212, 417, 112, 426};

    int allocationBlockNumber[4] = {-1, -1, -1, -1};

    int minSize;

    for(int i=0; i<4; i++) {
        minSize = -1;
        for(int j=1; j<5; j++) {
            if(blockSize[j] >= processSize[i]) {
                if(minSize == -1) minSize = j;
                else if(blockSize[j] < blockSize[minSize]) minSize = j;
            }
        }
        if(minSize == -1) continue;
        else {
            allocationBlockNumber[i] = minSize;
            blockSize[minSize] -= processSize[i];
        }
    }

    for(int i=0; i<4; i++) {
        if(allocationBlockNumber[i]!=-1)
            printf("Process %d allocated block: %d\n", i, allocationBlockNumber[i]);
        else
            printf("Process %d not allocated any space because of lack of space.\n", i);
    }
    return 0;
}