#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

# define PORTNO 4000

int sockfd,newsockfd,portno,clilen,n=1, arr[4];
struct sockaddr_in seraddr,cliaddr;
int i,value;

void createServerSocket() {
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));
    listen(sockfd,5);
}

void performServerSocket() {
    while(1){
        printf("Server Waiting\n");
        clilen = sizeof(clilen);
        newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&clilen);
        if(fork()==0){
            n = read(newsockfd,arr, sizeof(arr));
            if(arr[1]==0) arr[3]=arr[0]+arr[2];
            else if(arr[1]==1) arr[3]=arr[0]-arr[2];
            else if(arr[1]==2) arr[3]=arr[0]*arr[2];
            else if(arr[1]==3) arr[3]=arr[0]/arr[2];
            n = write(newsockfd,arr,sizeof(arr));
            close(newsockfd);
            exit(0);
        }
        else
        close(newsockfd);
    }
}


int main() {
    createServerSocket();
    performServerSocket();
    return 0;
    
}
