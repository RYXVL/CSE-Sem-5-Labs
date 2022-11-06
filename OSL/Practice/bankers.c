#include <stdio.h>
#include <stdlib.h>

int main() {
    int allocation[5][3] = {{0, 1, 0},
                            {2, 0, 0},
                            {3, 0, 2},
                            {2, 1, 1},
                            {0, 0, 2}};
    int max_need[5][3] =   {{7, 5, 3},
                            {3, 2, 2},
                            {9, 0, 2},
                            {2, 2, 2},
                            {4, 3, 3}};
    int avail[3] = {0, 1, 0};

    int need[5][3];
    for(int i=0; i<5; i++)
        for(int j=0; j<3; j++)
            need[i][j] = max_need[i][j] - allocation[i][j];
    
    int done[5];
    for(int i=0; i<5; i++)
        done[i] = 0;

    int flag = 1;
    int count;
    while(flag) {
        count = 0;
        for(int i=0; i<5; i++) {
            flag = 1;
            if(!done[i]) {
                for(int j=0; j<3; j++) {
                    if(need[i][j]>avail[j]) {
                        flag = 0;
                        break;
                    }
                }
                if(flag == 1) {
                    for(int j=0; j<3; j++)
                        avail[j]+=allocation[i][j];
                    printf("P%d ", i);
                    done[i] = 1;
                    break;
                }
                else count++;
            }
        }
        if(count==5) {
            printf("Safe sequence doesnt exist.\n");
            exit(0);
        }
        flag = 0;
        for(int i=0; i<5; i++)
            if(done[i]==0) {
                flag = 1;
                break;
            }
    }
    printf("Safe sequence found.\n");
    return 0;
}