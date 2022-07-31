#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORTNO 6001

int sockfd, newsockfd, portno, clilen, n = 1;
struct sockaddr_in seraddr, cliaddr;
int i, value;
char buff[256];

void createServerSocket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    printf("IP: 127.0.0.1 ; Ephimeral Port Number: %d\n", PORTNO);
    bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
}

void performServerTask() {
    while(1) {
        printf("Server Waiting\n");
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr, &clilen);
        n = read(newsockfd, buff, sizeof(buff));
        printf("Message from client: %s\n", buff);
        int i=0;
        while(buff[i]) {
            if(buff[i]>96 && buff[i]<122) buff[i]-=32;
            else {
                i++;
                continue;
            }
            i++;
        }
        n = write(newsockfd, buff, sizeof(buff));
    }
}

int main() {
    createServerSocket();
    performServerTask();
    return 0;
}
