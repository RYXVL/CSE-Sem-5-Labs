#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

# define PORTNO 5002

int sockfd,newsockfd,portno,clilen,n=1;
char buf[256];
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
            n = read(newsockfd,buf,sizeof(buf));
            printf(" \nMessage from Client %s \n",buf);
            n = write(newsockfd,buf,sizeof(buf));
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
