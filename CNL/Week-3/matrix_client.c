#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORTNO 5001

int main() {
    int sd;
    struct sockaddr_in address;
    sd=socket(AF_INET,SOCK_DGRAM,0);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("127.0.0.1");
    address.sin_port=htons(PORTNO);
    // char arr[25],arr1[25];
    // printf("enter arr\n");
    // gets(arr);
    int row, col;
    printf("Enter number of rows and cols: ");
    scanf("%d %d", &row, &col);
    int size = (row*col)+2;
    int arr[size];
    arr[0] = row;
    arr[1] = col;
    printf("Enter the rows of the matrix: ");
    for(int i=2; i<size; i++)
        scanf("%d", &(arr[i]));
        //check
    for(int i=0; i<size; i++)
        printf("%d ",arr[i]);
    int len=sizeof(address);
    int m=sendto(sd,arr,sizeof(arr),0,(struct sockaddr *)&address, len);
    // int n=recvfrom(sd,arr,sizeof(arr),0,(struct sockaddr *)&address,&len);
    // printf("the server echo is\n");
    // puts(arr);
    return 0;
}